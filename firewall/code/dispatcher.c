#include <pthread.h>

#include "utils/stopwatch.h"

#include "dispatcher.h"

dispatcher *init_dispatcher(int sources, worker **workers, PacketSource_t pks, int uniform_flag) {
	dispatcher *d = malloc(sizeof(dispatcher));
	d->pks = pks;
	d->sources = sources;
	d->workers = workers;
	d->time = 0;
	d->folded_time = 0;
	d->uniform = uniform_flag;
	d->fingerprint = 0;

	return(d);
}

void *execute_dispatcher(void *args) {
	dispatcher *d = args;
	int done = 0;

	StopWatch_t watch;
	startTimer(&watch);

	while(done < d->sources) {
		done = 0;
		for(int i = 0; i < d->sources; i++) {
			// skip over full worker queues and constantly checks for work to be done
			if(!is_full(d->workers[i]->queue) && d->workers[i]->p_remaining) {
				Packet_t *p;
				if(d->uniform) {
					p = (Packet_t *) getUniformPacket(&d->pks, i);
				} else {
					p = (Packet_t *) getExponentialPacket(&d->pks, i);
				}
				enq(d->workers[i]->queue, p);
				// logs to the worker that we have given it another task
				d->workers[i]->p_remaining--;
			}
			if(d->workers[i]->is_done) {
				done++;
			}
		}
	}

	stopTimer(&watch);
	d->folded_time = getElapsedTime(&watch);

	// get the spin wait time of the workers
	for(int i = 0; i < d->sources; i++) {
		d->time += d->workers[i]->time;
		d->fingerprint += d->workers[i]->fingerprint;
	}

	pthread_exit(NULL);
	return(NULL);
}
