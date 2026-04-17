all:
	gcc cache_hit_measure.c 
	./a.out single
	./a.out cache
	python3 stat.py

compil:
	gcc cache_hit_measure.c 

single:
	./a.out single

cache: 
	./a.out cache

stat:
	python3 stat.py

clean:
	rm a.out
	rm access_cache_hit.csv
	rm access_single.csv