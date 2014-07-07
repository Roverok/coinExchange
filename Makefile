
OBJ=net.o hiredis.o sds.o async.o
TESTS=mycoin-test



# Fallback to gcc when $CC is not in $PATH.
CXX:=$(shell sh -c 'type $(CC) >/dev/null 2>/dev/null && echo $(CC) || echo gcc')
CC:=$(shell sh -c 'type $(CC) >/dev/null 2>/dev/null && echo $(CC) || echo gcc')
OPTIMIZATION?=-O3
WARNINGS=-Wall -W -Wstrict-prototypes -Wwrite-strings
DEBUG?= -g -ggdb
REAL_CFLAGS=$(OPTIMIZATION) -fPIC $(CFLAGS) $(WARNINGS) $(DEBUG) $(ARCH)
REAL_LDFLAGS=$(LDFLAGS) $(ARCH)


STLIB_MAKE_CMD=ar rcs $(STLIBNAME)
LIB_DIR=/usr/local/lib
INCLUDE_DIR=/usr/local/include

VPATH = match:account

objects = message.o MessageProcessor.o QuoteQueue.o LevelOfQuoteQueue.o  QuoteMatchProcessor.o QuoteWithdrawProcessor.o Account.o DatabaseAccount.o AccountSuiteFactory.o BizAccount.o QuoteAccount.o  ContractNoteProcessor.o AccountExchangeProcessor.o  match.o aroundMatch.o RoutineQuotation.o RedisPublisher.o
all: mycoin test

# Deps (use make dep to generate this)


# Binaries:
message.o: message/message.c message/message.h
MessageProcessor.o: MessageProcessor.cpp MessageProcessor.h message/message.h

QuoteQueue.o: match/QuoteQueue.cpp match/QuoteQueue.h quote.h
LevelOfQuoteQueue.o: match/LevelOfQuoteQueue.cpp  match/LevelOfQuoteQueue.h quote.h
QuoteMatchProcessor.o: match/QuoteMatchProcessor.cpp match/QuoteMatchProcessor.h match/LimitPriceStrategy.h match/MarketPriceStrategy.h match/QuoteProcessor.h match/QuoteProcessorSet.h quote.h Singleton.h
QuoteWithdrawProcessor.o: match/QuoteWithdrawProcessor.cpp match/QuoteWithdrawProcessor.h quote.h Singleton.h



Account.o: account/Account.cpp account/Account.h
DatabaseAccount.o: account/DatabaseAccount.cpp account/DatabaseAccount.h account/Account.h
AccountSuiteFactory.o: account/AccountSuiteFactory.cpp account/AccountSuiteFactory.h account/DatabaseAccount.h account/Account.h
BizAccount.o: account/BizAccount.cpp account/BizAccount.h
QuoteAccount.o: account/QuoteAccount.cpp account/QuoteAccount.h account/MessageProcessor.h quote.h

ContractNoteProcessor.o: account/ContractNoteProcessor.cpp account/ContractNoteProcessor.h account/MessageProcessor.h quote.h
AccountExchangeProcessor.o: account/AccountExchangeProcessor.cpp account/AccountExchangeProcessor.h account/MessageProcessor.h quote.h


match.o: match.cpp match.h
RoutineQuotation.o: RoutineQuotation.cpp RoutineQuotation.h quote.h
RedisPublisher.o: RedisPublisher.cpp RedisPublisher.h quote.h RoutineQuotation.h
aroundMatch.o: aroundMatch.cpp aroundMatch.h RedisPublisher.h

mycoin: MycoinApplication.cpp MycoinApplication.h  $(objects)
	clang++ -v -std=c++11 -stdlib=libc++ -DWORK -o $@ $(REAL_CFLAGS) $(REAL_LDFLAGS) -I. -I$(INCLUDE_DIR) $<  $(objects) $(LIB_DIR)/libuv.dylib /Users/lx/work/soci-3.2.2/build/lib/libsoci_core.dylib /Users/lx/work/soci-3.2.2/build/lib/libsoci_sqlite3.dylib $(LIB_DIR)/libPocoUtil.dylib $(LIB_DIR)/libPocoFoundation.dylib $(LIB_DIR)/libPocoData.dylib  -L$(LIB_DIR) -lpthread -lhiredis

demo: demo.c demo.h quote.h
	$(CC) -o $@ $(REAL_LDFLAGS) $< $(LIB_DIR)/libuv.dylib -lpthread

.cpp.o:
	clang++ -std=c++11 -stdlib=libc++ -DWORK  -c  -I. -I$(INCLUDE_DIR) $<

.c.o:
	$(CC) -std=c99 -pedantic -c $(REAL_CFLAGS) -I. -I$(INCLUDE_DIR) $<

clean:
	-rm -rf $(TESTS) mycoin $(objects) *.gcda *.gcno *.gcov

dep:
	$(CC) -MM *.c


32bit:
	@echo ""
	@echo "WARNING: if this fails under Linux you probably need to install libc6-dev-i386"
	@echo ""
	$(MAKE) CFLAGS="-m32" LDFLAGS="-m32"

gprof:
	$(MAKE) CFLAGS="-pg" LDFLAGS="-pg"

gcov:
	$(MAKE) CFLAGS="-fprofile-arcs -ftest-coverage" LDFLAGS="-fprofile-arcs"

coverage: gcov
	make check
	mkdir -p tmp/lcov
	lcov -d . -c -o tmp/lcov/hiredis.info
	genhtml --legend -o tmp/lcov/report tmp/lcov/hiredis.info

noopt:
	$(MAKE) OPTIMIZATION=""

.PHONY: all test check clean dep install 32bit gprof gcov noopt
