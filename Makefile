IDIR=include
CC=gcc
CFLAGS=-I$(IDIR)

SRC=src
ODIR=obj

_DEPS = pointcloud.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = pointcloud.o
OBJ = $(patsubst %,$(SRC)/$(ODIR)/%,$(_OBJ))

$(SRC)/$(ODIR)/%.o: $(SRC)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

pointcloud: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(SRC)/$(ODIR)/*.o *~ core $(IDIR)/*~ 
