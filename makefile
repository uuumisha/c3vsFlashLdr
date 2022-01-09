# makefile for flashldr
# This makefile is for QNX 4.25

OBJDIR=release
INCDIR=inc
OUTFILE=flashldr

CC=cc 

LFLAGS= 
CFLAGS= -c -T1
OS = QNX 4.25
OBJ=  main.o flashldr.o tmk_kk.o tmk_driver.o ctrlsumm.o

target: $(OBJDIR)/$(OUTFILE)
	@echo
	@echo ======== COMPLETED
	@echo $(OUTFILE) for $(OS) processor created.
	@rm -f release/*.o
	@chmod a-x release/$(OUTFILE)
	@usemsg release/$(OUTFILE) inc/usage_inf 
	@chmod a+x release/$(OUTFILE)
 
$(OBJDIR)/$(OUTFILE): $(addprefix $(OBJDIR)/,$(OBJ))
	@echo
	@echo ======== LINKING $(OUTFILE) 
	$(CC) $(addprefix $(OBJDIR)/,$(OBJ))  $(LFLAGS) -o $@ 

$(OBJDIR)/%.o : %.c 
	@echo
	@echo ======== COMPILE $< ...
	$(CC) $(CFLAGS) $< -o $(OBJDIR)/
