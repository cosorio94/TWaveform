#---------------------------------------------------
CXXFLAGS      = -g -I/usr/local/include/root
#LDFLAGS       = -w -g `root-config --libs --cflags`
LDFLAGS       = -g -w -shared `root-config --libs --cflags`
LD            = c++
HDRS          = TWaveform.h TWaveformdict.h TWaveformConstants.h
SRCS          = TWaveform.cxx TWaveformdict.cxx TWaveformConstants.cxx
OBJS          = TWaveform.o TWaveformdict.o TWaveformConstants.o
PROGRAM       = TWaveform.so
all:            $(PROGRAM)
$(PROGRAM):     $(OBJS)
				@echo "Linking $(PROGRAM) ..."
				@/bin/rm -f $(PROGRAM)
				@$(LD) $(LDFLAGS) $(OBJS) -o $(PROGRAM)
				@chmod 555 $(PROGRAM)
				@echo "Done"
$(OBJS):		$(HDRS)
				@rootcint -f TWaveformdict.cxx -c TWaveform.h MyLinkDef.h
				@$(LD) $(LDFLAGS) $(SRCS) -c
clean:;			@rm -f $(OBJS) core
###
TWaveform.o: TWaveform.h
TWaveformConstants.o: TWaveformConstants.h
TWaveformdict.cxx: TWaveform.h MyLinkDef.h
	@echo "Generating dictionary ..."
	@rootcint -f TWaveformdict.cxx -c TWaveform.h MyLinkDef.h #---------------------------------------------------

.PHONY: all $(PROGRAM) $(OBJS) TWaveformdict.cxx
