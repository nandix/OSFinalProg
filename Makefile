CC = g++

#LIBS = -lpthread

FLAGS = -g -Wall

EXECS = dash mmu_simulation sched_sim paging_simulation

all: $(EXECS)

dash:
	$(MAKE) -C ./sim_shm_dash

mmu_simulation:
	$(MAKE) -C ./sim_mmu

sched_sim:
	$(MAKE) -C ./sim_scheduling

paging_simulation:
	$(MAKE) -C ./sim_page_repl

clean:
	$(RM) $(EXECS)

