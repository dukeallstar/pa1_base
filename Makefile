python:
	cd python;\
	python test.py


cpp:
	cd cpp;\
	g++ -lgtest pa1_unittests.cc -o ../tests_cpp
	./tests_cpp

clean:
	rm -f tests_cpp
