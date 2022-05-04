HELIB_INSTALL = /opt/helib_install/helib_pack
CXX = g++
CPPFLAGS = -I $(HELIB_INSTALL)/include/ -std=c++17 -O3
LIBS = -L $(HELIB_INSTALL)/lib/ -lntl -lhelib -lgmp -lpthread
BIN = ./bin
RM = rm -f
MKDIR_P = mkdir -p

all: directories leveled_latency_tests leveled_slots_tests bootstrap_tests

leveled_latency_tests: leveled_latency_depth2 leveled_latency_depth9 leveled_latency_depth17 leveled_latency_depth30

run_leveled_latency: leveled_latency_tests
	./bin/leveled_latency_depth2.out
	./bin/leveled_latency_depth9.out
	./bin/leveled_latency_depth17.out
	./bin/leveled_latency_depth30.out

leveled_slots_tests: leveled_slots_depth2 leveled_slots_depth9 leveled_slots_depth17 leveled_slots_depth30

run_leveled_slots: leveled_slots_tests
	./bin/leveled_slots_depth2.out
	./bin/leveled_slots_depth9.out
	./bin/leveled_slots_depth17.out
	./bin/leveled_slots_depth30.out

bootstrap_tests: boot_r1 boot_r4 boot_r8 boot_r12 boot_r16

run_bootstrap: bootstrap_tests
	./bin/boot_r1.out
	./bin/boot_r4.out
	./bin/boot_r8.out
	./bin/boot_r12.out
	./bin/boot_r16.out

run all: run_leveled_latency run_leveled_slots run_bootstrap

run leveled: run_leveled_latency run_leveled_slots

run bootstrapped: run_bootstrap

leveled_latency_depth2: $(BIN)/leveled_latency_depth2.o
	$(CXX) $(CPPFLAGS) $(BIN)/leveled_latency_depth2.o -o $(BIN)/leveled_latency_depth2.out $(LIBS)

$(BIN)/leveled_latency_depth2.o: leveled_exp/leveled_latency_depth2.cpp
	$(CXX) $(CPPFLAGS) -c leveled_exp/leveled_latency_depth2.cpp -o $(BIN)/leveled_latency_depth2.o

leveled_latency_depth9: $(BIN)/leveled_latency_depth9.o
	$(CXX) $(CPPFLAGS) $(BIN)/leveled_latency_depth9.o -o $(BIN)/leveled_latency_depth9.out $(LIBS)

$(BIN)/leveled_latency_depth9.o: leveled_exp/leveled_latency_depth9.cpp
	$(CXX) $(CPPFLAGS) -c leveled_exp/leveled_latency_depth9.cpp -o $(BIN)/leveled_latency_depth9.o

leveled_latency_depth17: $(BIN)/leveled_latency_depth17.o
	$(CXX) $(CPPFLAGS) $(BIN)/leveled_latency_depth17.o -o $(BIN)/leveled_latency_depth17.out $(LIBS)

$(BIN)/leveled_latency_depth17.o: leveled_exp/leveled_latency_depth17.cpp
	$(CXX) $(CPPFLAGS) -c leveled_exp/leveled_latency_depth17.cpp -o $(BIN)/leveled_latency_depth17.o

leveled_latency_depth30: $(BIN)/leveled_latency_depth30.o
	$(CXX) $(CPPFLAGS) $(BIN)/leveled_latency_depth30.o -o $(BIN)/leveled_latency_depth30.out $(LIBS)

$(BIN)/leveled_latency_depth30.o: leveled_exp/leveled_latency_depth30.cpp
	$(CXX) $(CPPFLAGS) -c leveled_exp/leveled_latency_depth30.cpp -o $(BIN)/leveled_latency_depth30.o

leveled_slots_depth2: $(BIN)/leveled_slots_depth2.o
	$(CXX) $(CPPFLAGS) $(BIN)/leveled_slots_depth2.o -o $(BIN)/leveled_slots_depth2.out $(LIBS)

$(BIN)/leveled_slots_depth2.o: leveled_exp/leveled_slots_depth2.cpp
	$(CXX) $(CPPFLAGS) -c leveled_exp/leveled_slots_depth2.cpp -o $(BIN)/leveled_slots_depth2.o

leveled_slots_depth9: $(BIN)/leveled_slots_depth9.o
	$(CXX) $(CPPFLAGS) $(BIN)/leveled_slots_depth9.o -o $(BIN)/leveled_slots_depth9.out $(LIBS)

$(BIN)/leveled_slots_depth9.o: leveled_exp/leveled_slots_depth9.cpp
	$(CXX) $(CPPFLAGS) -c leveled_exp/leveled_slots_depth9.cpp -o $(BIN)/leveled_slots_depth9.o

leveled_slots_depth17: $(BIN)/leveled_slots_depth17.o
	$(CXX) $(CPPFLAGS) $(BIN)/leveled_slots_depth17.o -o $(BIN)/leveled_slots_depth17.out $(LIBS)

$(BIN)/leveled_slots_depth17.o: leveled_exp/leveled_slots_depth17.cpp
	$(CXX) $(CPPFLAGS) -c leveled_exp/leveled_slots_depth17.cpp -o $(BIN)/leveled_slots_depth17.o

leveled_slots_depth30: $(BIN)/leveled_slots_depth30.o
	$(CXX) $(CPPFLAGS) $(BIN)/leveled_slots_depth30.o -o $(BIN)/leveled_slots_depth30.out $(LIBS)

$(BIN)/leveled_slots_depth30.o: leveled_exp/leveled_slots_depth30.cpp
	$(CXX) $(CPPFLAGS) -c leveled_exp/leveled_slots_depth30.cpp -o $(BIN)/leveled_slots_depth30.o

boot_r1: $(BIN)/boot_r1.o
	$(CXX) $(CPPFLAGS) $(BIN)/boot_r1.o -o $(BIN)/boot_r1.out $(LIBS)

$(BIN)/boot_r1.o: boot_exp/boot_r1.cpp
	$(CXX) $(CPPFLAGS) -c boot_exp/boot_r1.cpp -o $(BIN)/boot_r1.o

boot_r4: $(BIN)/boot_r4.o
	$(CXX) $(CPPFLAGS) $(BIN)/boot_r4.o -o $(BIN)/boot_r4.out $(LIBS)

$(BIN)/boot_r4.o: boot_exp/boot_r4.cpp
	$(CXX) $(CPPFLAGS) -c boot_exp/boot_r4.cpp -o $(BIN)/boot_r4.o

boot_r8: $(BIN)/boot_r8.o
	$(CXX) $(CPPFLAGS) $(BIN)/boot_r8.o -o $(BIN)/boot_r8.out $(LIBS)

$(BIN)/boot_r8.o: boot_exp/boot_r8.cpp
	$(CXX) $(CPPFLAGS) -c boot_exp/boot_r8.cpp -o $(BIN)/boot_r8.o

boot_r12: $(BIN)/boot_r12.o
	$(CXX) $(CPPFLAGS) $(BIN)/boot_r12.o -o $(BIN)/boot_r12.out $(LIBS)

$(BIN)/boot_r12.o: boot_exp/boot_r12.cpp
	$(CXX) $(CPPFLAGS) -c boot_exp/boot_r12.cpp -o $(BIN)/boot_r12.o

boot_r16: $(BIN)/boot_r16.o
	$(CXX) $(CPPFLAGS) $(BIN)/boot_r16.o -o $(BIN)/boot_r16.out $(LIBS)

$(BIN)/boot_r16.o: boot_exp/boot_r16.cpp
	$(CXX) $(CPPFLAGS) -c boot_exp/boot_r16.cpp -o $(BIN)/boot_r16.o

directories: ${BIN}

${BIN}:
	${MKDIR_P} ${BIN}

clean:
	$(RM) $(BIN)/*.o $(BIN)/*.out $(BIN)/*.log