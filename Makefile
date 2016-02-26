CXXFLAGS=-g -std=c++11

all: test main
	./test
	./main --docroot . --http-addr 0.0.0.0 --http-port 8080

test: opval.o \
      opval.t.o \
      FormModel.o \
      FormModel.t.o \
      FormView.o \
      FormView.t.o
	$(CXX) $+ -pthread -o test \
		/usr/lib/libQuantLib.a \
        /usr/lib/libwt.so \
        /usr/lib/libwttest.so \
		/usr/lib/libgtest.a \
		/usr/lib/libgtest_main.a
		#/usr/lib/libwt.so \

main: main.o opval.o FormView.o FormModel.o
	$(CXX) $+ -pthread -o main \
		/usr/lib/libQuantLib.a \
		/usr/lib/libwt.so \
		/usr/lib/libwthttp.so

clean:
	rm -f main test *.o
