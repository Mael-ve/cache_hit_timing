all:
	gcc same_bank_measure.c
	taskset -c 1 ./a.out
	python3 stat.py

compil:
	gcc same_bank_measure.c

stat:
	python3 stat.py

clean:
	rm a.out
	rm access_two_value.csv
