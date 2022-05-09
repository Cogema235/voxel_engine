all:
	gcc  -o a.out *.c -lm

clean:
	rm -f $(OBJS) $(OUT)
