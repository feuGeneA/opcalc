CXXFLAGS=-g -std=c++11 -Wall

all: test main
	./test

test: quantlib.o \
      quantlib.t.o \
      StringSetModel.o \
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

main: main.o quantlib.o StringSetModel.o FormModel.o FormView.o
	$(CXX) $+ -pthread -o main \
		/usr/lib/libQuantLib.a \
		/usr/lib/libwt.so \
		/usr/lib/libwthttp.so

clean:
	rm -f main test *.o
