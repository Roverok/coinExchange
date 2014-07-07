/******************************************************************* 
 * C file generated by Protoc for Embedded C.                      *
 * Version 1.0M4 (2013-03-31)                                      *
 *                                                                 *
 * Copyright (c) 2009-2013                                         *
 * Technische Universitaet Muenchen                                *
 * http://www4.in.tum.de/                                          *
 *                                                                 *
 * Source : message.proto
 *                                                                 *
 * Do not edit.                                                    *
 *******************************************************************/
 
#include "Message.h"

int _memcmp(const void *p1, const void *p2, unsigned int size) {
    unsigned int i;
    for(i = 0; i < size; ++ i) {
        if(*((char*)p1 + i) > *((char*)p2 + i))
            return 1;
        if(*((char*)p1 + i) < *((char*)p2 + i))
            return -1;
    }
    return 0;
} 
 
void _memset(void *msg_ptr, char init_val, unsigned int size) {
    unsigned int i;
    for(i = 0; i < size; ++ i)
        *((char*)msg_ptr + i) = init_val;
}

int varint_packed_size(unsigned long value) {
    if ((value & (0xffffffff <<  7)) == 0) return 1;
    if ((value & (0xffffffff << 14)) == 0) return 2;
    if ((value & (0xffffffff << 21)) == 0) return 3;
    if ((value & (0xffffffff << 28)) == 0) return 4;
    return 5;  
}

int write_raw_byte(char value, void *_buffer, int offset) {
    *((char *)_buffer + offset) = value;
    return ++offset;
}

/** Write a little-endian 32-bit integer. */
int write_raw_little_endian32(unsigned long value, void *_buffer, int offset) {
    offset = write_raw_byte((char)((value      ) & 0xFF), _buffer, offset);
    offset = write_raw_byte((char)((value >>  8) & 0xFF), _buffer, offset);
    offset = write_raw_byte((char)((value >> 16) & 0xFF), _buffer, offset);
    offset = write_raw_byte((char)((value >> 24) & 0xFF), _buffer, offset);
    
    return offset;
}

/** Write a little-endian 64-bit integer. */
int write_raw_little_endian64(unsigned long long value, void *_buffer, int offset) {
    offset = write_raw_byte((char)((value      ) & 0xFF), _buffer, offset);
    offset = write_raw_byte((char)((value >>  8) & 0xFF), _buffer, offset);
    offset = write_raw_byte((char)((value >> 16) & 0xFF), _buffer, offset);
    offset = write_raw_byte((char)((value >> 24) & 0xFF), _buffer, offset);
    offset = write_raw_byte((char)((value >> 32) & 0xFF), _buffer, offset);
    offset = write_raw_byte((char)((value >> 40) & 0xFF), _buffer, offset);
    offset = write_raw_byte((char)((value >> 48) & 0xFF), _buffer, offset);
    offset = write_raw_byte((char)((value >> 56) & 0xFF), _buffer, offset);
    
    return offset;
}

int write_raw_varint32(unsigned long value, void *_buffer, int offset) {
    while (1) {
        if ((value & ~0x7F) == 0) {
            offset = write_raw_byte((char)value, _buffer, offset);
            return offset;
        } else {
            offset = write_raw_byte((char)((value & 0x7F) | 0x80), _buffer, offset);
            value = value >> 7;
        }
    }
    return offset;
}

int write_raw_varint64(unsigned long long value, void *_buffer, int offset) {
    while (1) {
        if ((value & ~0x7FL) == 0) {
            offset = write_raw_byte((char)value, _buffer, offset);
            return offset;
        } else {
            offset = write_raw_byte((char)((value & 0x7F) | 0x80), _buffer, offset);
            value = value >> 7;
        }
    }
    return offset;
}

int write_raw_bytes(char *bytes, int bytes_size, void *_buffer, int offset) {
    int i; 
    for(i = 0; i < bytes_size; ++ i) {
        offset = write_raw_byte((char)*(bytes + i), _buffer, offset);
    }
    
    return offset;   
}

unsigned long encode_zig_zag32(signed long n) {
    /* Note:  the right-shift must be arithmetic. */
    return (n << 1) ^ (n >> 31);
}

unsigned long long encode_zig_zag64(signed long long n) {
    /* Note:  the right-shift must be arithmetic. */
    return (n << 1) ^ (n >> 63);
} 

signed long decode_zig_zag32(unsigned long n) {
    return (n >> 1) ^ -(n & 1);
}

signed long long decode_zig_zag64(unsigned long long n) {
    return (n >> 1) ^ -(n & 1);
}

int read_raw_byte(char *tag, void *_buffer, int offset) {
    *tag = *((char *) _buffer + offset);
    
    return ++offset;
}

/** Read a 32-bit little-endian integer from the stream. */
int read_raw_little_endian32(unsigned long *tag, void *_buffer, int offset) {
    offset = read_raw_byte((char *)tag, _buffer, offset);
    char b1 = (char) *tag;
    offset = read_raw_byte((char *)tag, _buffer, offset);
    char b2 = (char) *tag;
    offset = read_raw_byte((char *)tag, _buffer, offset);
    char b3 = (char) *tag;
    offset = read_raw_byte((char *)tag, _buffer, offset);
    char b4 = (char) *tag;
    
    *tag = (((unsigned long)b1 & 0xff)      ) |
           (((unsigned long)b2 & 0xff) <<  8) |
           (((unsigned long)b3 & 0xff) << 16) |
           (((unsigned long)b4 & 0xff) << 24);
           
    return offset;
}

/** Read a 64-bit little-endian integer from the stream. */
int read_raw_little_endian64(unsigned long long *tag, void *_buffer, int offset) {
    offset = read_raw_byte((char *)tag, _buffer, offset);
    char b1 = (char) *tag;
    offset = read_raw_byte((char *)tag, _buffer, offset);
    char b2 = (char) *tag;
    offset = read_raw_byte((char *)tag, _buffer, offset);
    char b3 = (char) *tag;
    offset = read_raw_byte((char *)tag, _buffer, offset);
    char b4 = (char) *tag;
    offset = read_raw_byte((char *)tag, _buffer, offset);
    char b5 = (char) *tag;
    offset = read_raw_byte((char *)tag, _buffer, offset);
    char b6 = (char) *tag;
    offset = read_raw_byte((char *)tag, _buffer, offset);
    char b7 = (char) *tag;
    offset = read_raw_byte((char *)tag, _buffer, offset);
    char b8 = (char) *tag;
    
    *tag = (((unsigned long long)b1 & 0xff)      ) |
           (((unsigned long long)b2 & 0xff) <<  8) |
           (((unsigned long long)b3 & 0xff) << 16) |
           (((unsigned long long)b4 & 0xff) << 24) |
           (((unsigned long long)b5 & 0xff) << 32) |
           (((unsigned long long)b6 & 0xff) << 40) |
           (((unsigned long long)b7 & 0xff) << 48) |
           (((unsigned long long)b8 & 0xff) << 56);
           
    return offset;
}

int read_raw_varint32(unsigned long *tag, void *_buffer, int offset) {
    signed char result;
    
    offset = read_raw_byte((char *)&result, _buffer, offset);
    if (result >= 0) {
        *tag = result;
        return offset;
    }
    *tag = result & 0x7f;
    offset = read_raw_byte((char *)&result, _buffer, offset);
    if (result >= 0) {
        *tag |= result << 7;
    } else {
        *tag |= (result & 0x7f) << 7;
        offset = read_raw_byte((char *)&result, _buffer, offset);
        if (result >= 0) {
            *tag |= result << 14;
        } else {
            *tag |= (result & 0x7f) << 14;
            offset = read_raw_byte((char *)&result, _buffer, offset);
            if (result >= 0) {
                *tag |= ((unsigned long)result) << 21;
            } else {
                *tag |= (((unsigned long)result) & 0x7f) << 21;
                offset = read_raw_byte((char *)&result, _buffer, offset);
                *tag |= ((unsigned long)result) << 28;
                if (result < 0) {
                    /* Discard upper 32 bits. */
                    int i;
                    for (i = 0; i < 5; ++ i) {
                        offset = read_raw_byte((char *)&result, _buffer, offset);
                        if (result >= 0) {
                            return offset;
                        }
                    }
                    /* Invalid state. */
                }
            }
        }
    }
    return offset;
}

int read_raw_varint64(unsigned long long *tag, void *_buffer, int offset) {
    short shift = 0;
    signed char b;
    *tag = 0;
    while (shift < 64) {
        offset = read_raw_byte((char *)&b, _buffer, offset);
        *tag |= (unsigned long long)(b & 0x7F) << shift;
        if ((b & 0x80) == 0) {
            return offset;
        }
        shift += 7;
    }
    /* return error code. */
    return -1;
}

int can_read_raw_varint32(void *_buffer, int offset, int length) {
    signed char c;
    
    /* Bound length to valid range [0..5]. */
    if (length < 0) length = 0; else
    if (length > 5) length = 5;
    
    while (length > 0) {
        offset = read_raw_byte((char *)&c, _buffer, offset);
        if (c >= 0) {
            return 1; /* Can read (1 == true). */
        }
        length--;
    }
    
    return 0; /* Cannot read (0 == false). */
}

int can_read_raw_varint64(void *_buffer, int offset, int length) {
    signed char c;
    
    /* Bound length to valid range [0..5]. */
    if (length < 0) length = 0; else
    if (length > 10) length = 10;
    
    while (length > 0) {
        offset = read_raw_byte((char *)&c, _buffer, offset);
        if (c >= 0) {
            return 1; /* Can read (1 == true). */
        }
        length--;
    }
    
    return 0; /* Cannot read (0 == false). */
}

int Message_can_read_delimited_from(void *_buffer, int offset, unsigned int length) {
    unsigned long size;
    int payload_offset;

    if (length <= 0) return 0; /* Cannot read from empty or invalid message. */

    if (!can_read_raw_varint32(_buffer, offset, length)) {
        return 0; /* Could not even read the preceding size as varint32. */
    }

    payload_offset = read_raw_varint32(&size, _buffer, offset);
    length = length - (payload_offset - offset);

    return (length >= size) ? 1 : 0;
}

unsigned long Message_get_delimited_size(void *_buffer, int offset) {
    unsigned long size = 0;
    int old_offset = offset;
    
    offset = read_raw_varint32(&size, _buffer, offset);
    
    return size + offset - old_offset;
}

/*******************************************************************
* Enumeration: Message.proto, line 26
*******************************************************************/
int message_type_t_write_with_tag(enum message_type_t *_message_type_t, void *_buffer, int offset, int tag) {
    /* Write tag.*/
    offset = write_raw_varint32((tag<<3)+0, _buffer, offset);
    /* Write content.*/
    offset = write_raw_varint32(*_message_type_t, _buffer, offset);
    
    return offset;
}

/*******************************************************************
* Enumeration: Message.proto, line 17
*******************************************************************/
int bill_status_t_write_with_tag(enum bill_status_t *_bill_status_t, void *_buffer, int offset, int tag) {
    /* Write tag.*/
    offset = write_raw_varint32((tag<<3)+0, _buffer, offset);
    /* Write content.*/
    offset = write_raw_varint32(*_bill_status_t, _buffer, offset);
    
    return offset;
}

/*******************************************************************
* Enumeration: Message.proto, line 5
*******************************************************************/
int security_bill_t_write_with_tag(enum security_bill_t *_security_bill_t, void *_buffer, int offset, int tag) {
    /* Write tag.*/
    offset = write_raw_varint32((tag<<3)+0, _buffer, offset);
    /* Write content.*/
    offset = write_raw_varint32(*_security_bill_t, _buffer, offset);
    
    return offset;
}


/*******************************************************************
 * Message: Message.proto, line 35
 *******************************************************************/

void SecurityQuote_clear(struct SecurityQuote *_SecurityQuote) {
	_memset(_SecurityQuote, 0, sizeof(struct SecurityQuote));
}

void SecurityQuote_init_optional_attributes(struct SecurityQuote *_SecurityQuote) {
}

int SecurityQuote_is_default_message(struct SecurityQuote *_SecurityQuote) {
    return _SecurityQuote->msg_type == 0
    
     && _SecurityQuote->billType == 0
    
     && _SecurityQuote->billId == 0
    
     && _SecurityQuote->occurTime == 0
    
     && _SecurityQuote->status == 0
    
     && _SecurityQuote->code == 0
    
     && _SecurityQuote->price == 0
    
     && _SecurityQuote->quality == 0
    
     && _SecurityQuote->_guaranty == 0
    
     && _SecurityQuote->_client_len == 0
    ;
}

int SecurityQuote_write(struct SecurityQuote *_SecurityQuote, void *_buffer, int offset) {
	/* Write content of each message element.*/
	offset = message_type_t_write_with_tag(&_SecurityQuote->msg_type, _buffer, offset, 1);
	
	offset = security_bill_t_write_with_tag(&_SecurityQuote->billType, _buffer, offset, 2);
	
	offset = write_raw_varint32((3<<3)+0, _buffer, offset);
	offset = write_raw_varint32(_SecurityQuote->billId, _buffer, offset);
	
	offset = write_raw_varint32((4<<3)+0, _buffer, offset);
	offset = write_raw_varint32(_SecurityQuote->occurTime, _buffer, offset);
	
	offset = bill_status_t_write_with_tag(&_SecurityQuote->status, _buffer, offset, 5);
	
	offset = write_raw_varint32((6<<3)+0, _buffer, offset);
	offset = write_raw_varint64(_SecurityQuote->code, _buffer, offset);
	
	offset = write_raw_varint32((7<<3)+0, _buffer, offset);
	offset = write_raw_varint32(_SecurityQuote->price, _buffer, offset);
	
	offset = write_raw_varint32((8<<3)+0, _buffer, offset);
	offset = write_raw_varint32(_SecurityQuote->quality, _buffer, offset);
	
	offset = write_raw_varint32((9<<3)+0, _buffer, offset);
	offset = write_raw_varint32(_SecurityQuote->_guaranty, _buffer, offset);
	
	offset = write_raw_varint32((10<<3)+2, _buffer, offset);
	offset = write_raw_varint32(_SecurityQuote->_client_len, _buffer, offset);
	offset = write_raw_bytes(_SecurityQuote->client, _SecurityQuote->_client_len, _buffer, offset);
	
	return offset;
}

int SecurityQuote_write_with_tag(struct SecurityQuote *_SecurityQuote, void *_buffer, int offset, int tag) {
	/* Write tag.*/
	offset = write_raw_varint32((tag<<3)+2, _buffer, offset);
	/* Write content.*/
	offset = SecurityQuote_write_delimited_to(_SecurityQuote, _buffer, offset);
	
	return offset;
}

int SecurityQuote_write_delimited_to(struct SecurityQuote *_SecurityQuote, void *_buffer, int offset) {
	int i, shift, new_offset, size;
	
	new_offset = SecurityQuote_write(_SecurityQuote, _buffer, offset);
	size = new_offset - offset;
	shift = (size > 127) ? 2 : 1;
	for (i = new_offset - 1; i >= offset; -- i)
	    *((char *)_buffer + i + shift) = *((char *)_buffer + i);
	
	write_raw_varint32((unsigned long) size, _buffer, offset);         
	    
	return new_offset + shift;
}

int SecurityQuote_read(void *_buffer, struct SecurityQuote *_SecurityQuote, int offset, int limit) {
	unsigned int i = 0;
	unsigned long long value = i;
	unsigned long tag = value;
	
	/* Reset all attributes to 0 in advance. */
	SecurityQuote_clear(_SecurityQuote);
	/* Assign the optional attributes. */
	SecurityQuote_init_optional_attributes(_SecurityQuote);
	
	/* Read/interpret all attributes from buffer offset until upper limit is reached. */
	while(offset < limit) {
	    offset = read_raw_varint32(&tag, _buffer, offset);
		tag = tag>>3;
	    switch(tag){
	        /* tag of: _SecurityQuote.msg_type */
	        case 1 :
	        	offset = read_raw_varint32(&tag, _buffer, offset);
	        	_SecurityQuote->msg_type = tag;
	        	break;
	        /* tag of: _SecurityQuote.billType */
	        case 2 :
	        	offset = read_raw_varint32(&tag, _buffer, offset);
	        	_SecurityQuote->billType = tag;
	        	break;
	        /* tag of: _SecurityQuote.billId */
	        case 3 :
	        	offset = read_raw_varint32(&tag, _buffer, offset);
	        	_SecurityQuote->billId = tag;
	        	break;
	        /* tag of: _SecurityQuote.occurTime */
	        case 4 :
	        	offset = read_raw_varint32(&tag, _buffer, offset);
	        	_SecurityQuote->occurTime = tag;
	        	break;
	        /* tag of: _SecurityQuote._status */
	        case 5 :
	        	offset = read_raw_varint32(&tag, _buffer, offset);
	        	_SecurityQuote->status = tag;
	        	break;
	        /* tag of: _SecurityQuote._code */
	        case 6 :
	        	offset = read_raw_varint64(&value, _buffer, offset);
	        	_SecurityQuote->code = value;
	        	break;
	        /* tag of: _SecurityQuote._price */
	        case 7 :
	        	offset = read_raw_varint32(&tag, _buffer, offset);
	        	_SecurityQuote->price = tag;
	        	break;
	        /* tag of: _SecurityQuote._quality */
	        case 8 :
	        	offset = read_raw_varint32(&tag, _buffer, offset);
	        	_SecurityQuote->quality = tag;
	        	break;
	        /* tag of: _SecurityQuote._guaranty */
	        case 9 :
	        	offset = read_raw_varint32(&tag, _buffer, offset);
	        	_SecurityQuote->_guaranty = tag;
	        	break;
	        /* tag of: _SecurityQuote._client */
	        case 10 :
	        	/* Re-use 'tag' to store string length. */
	        	offset = read_raw_varint32(&tag, _buffer, offset);
	        	_SecurityQuote->_client_len = tag;
	        	for(i = 0; i < tag; ++ i) 
	        	    offset = read_raw_byte((_SecurityQuote->client + i), _buffer, offset);
	        	break;
	    }
	}
	
	return offset;
}

int SecurityQuote_read_delimited_from(void *_buffer, struct SecurityQuote *_SecurityQuote, int offset) {
	unsigned long size;
	
	offset = read_raw_varint32(&size, _buffer, offset);
	SecurityQuote_read(_buffer, _SecurityQuote, offset, size + offset);
	
	return offset + size;
}
/*******************************************************************
 * Message: Message.proto, line 49
 *******************************************************************/

void WithdrawQuote_clear(struct WithdrawQuote *_WithdrawQuote) {
	_memset(_WithdrawQuote, 0, sizeof(struct WithdrawQuote));
}

void WithdrawQuote_init_optional_attributes(struct WithdrawQuote *_WithdrawQuote) {
}

int WithdrawQuote_is_default_message(struct WithdrawQuote *_WithdrawQuote) {
    return _WithdrawQuote->msg_type == 0
    
     && _WithdrawQuote->billType == 0
    
     && _WithdrawQuote->billId == 0
    
     && _WithdrawQuote->occurTime == 0
    
     && _WithdrawQuote->status == 0
    
     && _WithdrawQuote->code == 0
    
     && _WithdrawQuote->refBillId == 0
    
     && _WithdrawQuote->_client_len == 0
    ;
}

int WithdrawQuote_write(struct WithdrawQuote *_WithdrawQuote, void *_buffer, int offset) {
	/* Write content of each message element.*/
	offset = message_type_t_write_with_tag(&_WithdrawQuote->msg_type, _buffer, offset, 1);
	
	offset = security_bill_t_write_with_tag(&_WithdrawQuote->billType, _buffer, offset, 2);
	
	offset = write_raw_varint32((3<<3)+0, _buffer, offset);
	offset = write_raw_varint32(_WithdrawQuote->billId, _buffer, offset);
	
	offset = write_raw_varint32((4<<3)+0, _buffer, offset);
	offset = write_raw_varint32(_WithdrawQuote->occurTime, _buffer, offset);
	
	offset = bill_status_t_write_with_tag(&_WithdrawQuote->status, _buffer, offset, 5);
	
	offset = write_raw_varint32((6<<3)+0, _buffer, offset);
	offset = write_raw_varint64(_WithdrawQuote->code, _buffer, offset);
	
	offset = write_raw_varint32((7<<3)+0, _buffer, offset);
	offset = write_raw_varint32(_WithdrawQuote->refBillId, _buffer, offset);
	
	offset = write_raw_varint32((8<<3)+2, _buffer, offset);
	offset = write_raw_varint32(_WithdrawQuote->_client_len, _buffer, offset);
	offset = write_raw_bytes(_WithdrawQuote->client, _WithdrawQuote->_client_len, _buffer, offset);
	
	return offset;
}

int WithdrawQuote_write_with_tag(struct WithdrawQuote *_WithdrawQuote, void *_buffer, int offset, int tag) {
	/* Write tag.*/
	offset = write_raw_varint32((tag<<3)+2, _buffer, offset);
	/* Write content.*/
	offset = WithdrawQuote_write_delimited_to(_WithdrawQuote, _buffer, offset);
	
	return offset;
}

int WithdrawQuote_write_delimited_to(struct WithdrawQuote *_WithdrawQuote, void *_buffer, int offset) {
	int i, shift, new_offset, size;
	
	new_offset = WithdrawQuote_write(_WithdrawQuote, _buffer, offset);
	size = new_offset - offset;
	shift = (size > 127) ? 2 : 1;
	for (i = new_offset - 1; i >= offset; -- i)
	    *((char *)_buffer + i + shift) = *((char *)_buffer + i);
	
	write_raw_varint32((unsigned long) size, _buffer, offset);         
	    
	return new_offset + shift;
}

int WithdrawQuote_read(void *_buffer, struct WithdrawQuote *_WithdrawQuote, int offset, int limit) {
	unsigned int i = 0;
	unsigned long long value = i;
	unsigned long tag = value;
	
	/* Reset all attributes to 0 in advance. */
	WithdrawQuote_clear(_WithdrawQuote);
	/* Assign the optional attributes. */
	WithdrawQuote_init_optional_attributes(_WithdrawQuote);
	
	/* Read/interpret all attributes from buffer offset until upper limit is reached. */
	while(offset < limit) {
	    offset = read_raw_varint32(&tag, _buffer, offset);
		tag = tag>>3;
	    switch(tag){
	        /* tag of: _WithdrawQuote.msg_type */
	        case 1 :
	        	offset = read_raw_varint32(&tag, _buffer, offset);
	        	_WithdrawQuote->msg_type = tag;
	        	break;
	        /* tag of: _WithdrawQuote.billType */
	        case 2 :
	        	offset = read_raw_varint32(&tag, _buffer, offset);
	        	_WithdrawQuote->billType = tag;
	        	break;
	        /* tag of: _WithdrawQuote.billId */
	        case 3 :
	        	offset = read_raw_varint32(&tag, _buffer, offset);
	        	_WithdrawQuote->billId = tag;
	        	break;
	        /* tag of: _WithdrawQuote.occurTime */
	        case 4 :
	        	offset = read_raw_varint32(&tag, _buffer, offset);
	        	_WithdrawQuote->occurTime = tag;
	        	break;
	        /* tag of: _WithdrawQuote._status */
	        case 5 :
	        	offset = read_raw_varint32(&tag, _buffer, offset);
	        	_WithdrawQuote->status = tag;
	        	break;
	        /* tag of: _WithdrawQuote._code */
	        case 6 :
	        	offset = read_raw_varint64(&value, _buffer, offset);
	        	_WithdrawQuote->code = value;
	        	break;
	        /* tag of: _WithdrawQuote._refBillId */
	        case 7 :
	        	offset = read_raw_varint32(&tag, _buffer, offset);
	        	_WithdrawQuote->refBillId = tag;
	        	break;
	        /* tag of: _WithdrawQuote._client */
	        case 8 :
	        	/* Re-use 'tag' to store string length. */
	        	offset = read_raw_varint32(&tag, _buffer, offset);
	        	_WithdrawQuote->_client_len = tag;
	        	for(i = 0; i < tag; ++ i) 
	        	    offset = read_raw_byte((_WithdrawQuote->client + i), _buffer, offset);
	        	break;
	    }
	}
	
	return offset;
}

int WithdrawQuote_read_delimited_from(void *_buffer, struct WithdrawQuote *_WithdrawQuote, int offset) {
	unsigned long size;
	
	offset = read_raw_varint32(&size, _buffer, offset);
	WithdrawQuote_read(_buffer, _WithdrawQuote, offset, size + offset);
	
	return offset + size;
}
/*******************************************************************
 * Message: Message.proto, line 61
 *******************************************************************/

void ContractNote_clear(struct ContractNote *_ContractNote) {
	_memset(_ContractNote, 0, sizeof(struct ContractNote));
}

void ContractNote_init_optional_attributes(struct ContractNote *_ContractNote) {
}

int ContractNote_is_default_message(struct ContractNote *_ContractNote) {
    return _ContractNote->msg_type == 0
    
     && _ContractNote->billType == 0
    
     && _ContractNote->billId == 0
    
     && _ContractNote->occurTime == 0
    
     && _ContractNote->status == 0
    
     && _ContractNote->code == 0
    
     && _ContractNote->price == 0
    
     && _ContractNote->quality == 0
    
     && _ContractNote->sourceBillId == 0
    
     && _ContractNote->peerBillId == 0
    
     && _ContractNote->_buyer_len == 0
    
     && _ContractNote->_seller_len == 0
    ;
}

int ContractNote_write(struct ContractNote *_ContractNote, void *_buffer, int offset) {
	/* Write content of each message element.*/
	offset = message_type_t_write_with_tag(&_ContractNote->msg_type, _buffer, offset, 1);
	
	offset = security_bill_t_write_with_tag(&_ContractNote->billType, _buffer, offset, 2);
	
	offset = write_raw_varint32((3<<3)+0, _buffer, offset);
	offset = write_raw_varint32(_ContractNote->billId, _buffer, offset);
	
	offset = write_raw_varint32((4<<3)+0, _buffer, offset);
	offset = write_raw_varint32(_ContractNote->occurTime, _buffer, offset);
	
	offset = bill_status_t_write_with_tag(&_ContractNote->status, _buffer, offset, 5);
	
	offset = write_raw_varint32((6<<3)+0, _buffer, offset);
	offset = write_raw_varint64(_ContractNote->code, _buffer, offset);
	
	offset = write_raw_varint32((7<<3)+0, _buffer, offset);
	offset = write_raw_varint32(_ContractNote->price, _buffer, offset);
	
	offset = write_raw_varint32((8<<3)+0, _buffer, offset);
	offset = write_raw_varint32(_ContractNote->quality, _buffer, offset);
	
	offset = write_raw_varint32((9<<3)+0, _buffer, offset);
	offset = write_raw_varint32(_ContractNote->sourceBillId, _buffer, offset);
	
	offset = write_raw_varint32((10<<3)+0, _buffer, offset);
	offset = write_raw_varint32(_ContractNote->peerBillId, _buffer, offset);
	
	offset = write_raw_varint32((11<<3)+2, _buffer, offset);
	offset = write_raw_varint32(_ContractNote->_buyer_len, _buffer, offset);
	offset = write_raw_bytes(_ContractNote->buyer, _ContractNote->_buyer_len, _buffer, offset);
	
	offset = write_raw_varint32((12<<3)+2, _buffer, offset);
	offset = write_raw_varint32(_ContractNote->_seller_len, _buffer, offset);
	offset = write_raw_bytes(_ContractNote->seller, _ContractNote->_seller_len, _buffer, offset);
	
	return offset;
}

int ContractNote_write_with_tag(struct ContractNote *_ContractNote, void *_buffer, int offset, int tag) {
	/* Write tag.*/
	offset = write_raw_varint32((tag<<3)+2, _buffer, offset);
	/* Write content.*/
	offset = ContractNote_write_delimited_to(_ContractNote, _buffer, offset);
	
	return offset;
}

int ContractNote_write_delimited_to(struct ContractNote *_ContractNote, void *_buffer, int offset) {
	int i, shift, new_offset, size;
	
	new_offset = ContractNote_write(_ContractNote, _buffer, offset);
	size = new_offset - offset;
	shift = (size > 127) ? 2 : 1;
	for (i = new_offset - 1; i >= offset; -- i)
	    *((char *)_buffer + i + shift) = *((char *)_buffer + i);
	
	write_raw_varint32((unsigned long) size, _buffer, offset);         
	    
	return new_offset + shift;
}

int ContractNote_read(void *_buffer, struct ContractNote *_ContractNote, int offset, int limit) {
	unsigned int i = 0;
	unsigned long long value = i;
	unsigned long tag = value;
	
	/* Reset all attributes to 0 in advance. */
	ContractNote_clear(_ContractNote);
	/* Assign the optional attributes. */
	ContractNote_init_optional_attributes(_ContractNote);
	
	/* Read/interpret all attributes from buffer offset until upper limit is reached. */
	while(offset < limit) {
	    offset = read_raw_varint32(&tag, _buffer, offset);
		tag = tag>>3;
	    switch(tag){
	        /* tag of: _ContractNote.msg_type */
	        case 1 :
	        	offset = read_raw_varint32(&tag, _buffer, offset);
	        	_ContractNote->msg_type = tag;
	        	break;
	        /* tag of: _ContractNote.billType */
	        case 2 :
	        	offset = read_raw_varint32(&tag, _buffer, offset);
	        	_ContractNote->billType = tag;
	        	break;
	        /* tag of: _ContractNote.billId */
	        case 3 :
	        	offset = read_raw_varint32(&tag, _buffer, offset);
	        	_ContractNote->billId = tag;
	        	break;
	        /* tag of: _ContractNote.occurTime */
	        case 4 :
	        	offset = read_raw_varint32(&tag, _buffer, offset);
	        	_ContractNote->occurTime = tag;
	        	break;
	        /* tag of: _ContractNote._status */
	        case 5 :
	        	offset = read_raw_varint32(&tag, _buffer, offset);
	        	_ContractNote->status = tag;
	        	break;
	        /* tag of: _ContractNote._code */
	        case 6 :
	        	offset = read_raw_varint64(&value, _buffer, offset);
	        	_ContractNote->code = value;
	        	break;
	        /* tag of: _ContractNote._price */
	        case 7 :
	        	offset = read_raw_varint32(&tag, _buffer, offset);
	        	_ContractNote->price = tag;
	        	break;
	        /* tag of: _ContractNote._quality */
	        case 8 :
	        	offset = read_raw_varint32(&tag, _buffer, offset);
	        	_ContractNote->quality = tag;
	        	break;
	        /* tag of: _ContractNote._sourceBillId */
	        case 9 :
	        	offset = read_raw_varint32(&tag, _buffer, offset);
	        	_ContractNote->sourceBillId = tag;
	        	break;
	        /* tag of: _ContractNote._peerBillId */
	        case 10 :
	        	offset = read_raw_varint32(&tag, _buffer, offset);
	        	_ContractNote->peerBillId = tag;
	        	break;
	        /* tag of: _ContractNote._buyer */
	        case 11 :
	        	/* Re-use 'tag' to store string length. */
	        	offset = read_raw_varint32(&tag, _buffer, offset);
	        	_ContractNote->_buyer_len = tag;
	        	for(i = 0; i < tag; ++ i) 
	        	    offset = read_raw_byte((_ContractNote->buyer + i), _buffer, offset);
	        	break;
	        /* tag of: _ContractNote._seller */
	        case 12 :
	        	/* Re-use 'tag' to store string length. */
	        	offset = read_raw_varint32(&tag, _buffer, offset);
	        	_ContractNote->_seller_len = tag;
	        	for(i = 0; i < tag; ++ i) 
	        	    offset = read_raw_byte((_ContractNote->seller + i), _buffer, offset);
	        	break;
	    }
	}
	
	return offset;
}

int ContractNote_read_delimited_from(void *_buffer, struct ContractNote *_ContractNote, int offset) {
	unsigned long size;
	
	offset = read_raw_varint32(&size, _buffer, offset);
	ContractNote_read(_buffer, _ContractNote, offset, size + offset);
	
	return offset + size;
}
/*******************************************************************
 * Message: Message.proto, line 78
 *******************************************************************/

void AccountExchangeNote_clear(struct AccountExchangeNote *_AccountExchangeNote) {
	_memset(_AccountExchangeNote, 0, sizeof(struct AccountExchangeNote));
}

void AccountExchangeNote_init_optional_attributes(struct AccountExchangeNote *_AccountExchangeNote) {
}

int AccountExchangeNote_is_default_message(struct AccountExchangeNote *_AccountExchangeNote) {
    return _AccountExchangeNote->msg_type == 0
    
     && _AccountExchangeNote->billType == 0
    
     && _AccountExchangeNote->billId == 0
    
     && _AccountExchangeNote->occurTime == 0
    
     && _AccountExchangeNote->status == 0
    
     && _AccountExchangeNote->code == 0
    
     && _AccountExchangeNote->quality == 0
    
     && _AccountExchangeNote->_client_len == 0
    ;
}

int AccountExchangeNote_write(struct AccountExchangeNote *_AccountExchangeNote, void *_buffer, int offset) {
	/* Write content of each message element.*/
	offset = message_type_t_write_with_tag(&_AccountExchangeNote->msg_type, _buffer, offset, 1);
	
	offset = security_bill_t_write_with_tag(&_AccountExchangeNote->billType, _buffer, offset, 2);
	
	offset = write_raw_varint32((3<<3)+0, _buffer, offset);
	offset = write_raw_varint32(_AccountExchangeNote->billId, _buffer, offset);
	
	offset = write_raw_varint32((4<<3)+0, _buffer, offset);
	offset = write_raw_varint32(_AccountExchangeNote->occurTime, _buffer, offset);
	
	offset = bill_status_t_write_with_tag(&_AccountExchangeNote->status, _buffer, offset, 5);
	
	offset = write_raw_varint32((6<<3)+0, _buffer, offset);
	offset = write_raw_varint64(_AccountExchangeNote->code, _buffer, offset);
	
	offset = write_raw_varint32((7<<3)+0, _buffer, offset);
	offset = write_raw_varint32(_AccountExchangeNote->quality, _buffer, offset);
	
	offset = write_raw_varint32((8<<3)+2, _buffer, offset);
	offset = write_raw_varint32(_AccountExchangeNote->_client_len, _buffer, offset);
	offset = write_raw_bytes(_AccountExchangeNote->client, _AccountExchangeNote->_client_len, _buffer, offset);
	
	return offset;
}

int AccountExchangeNote_write_with_tag(struct AccountExchangeNote *_AccountExchangeNote, void *_buffer, int offset, int tag) {
	/* Write tag.*/
	offset = write_raw_varint32((tag<<3)+2, _buffer, offset);
	/* Write content.*/
	offset = AccountExchangeNote_write_delimited_to(_AccountExchangeNote, _buffer, offset);
	
	return offset;
}

int AccountExchangeNote_write_delimited_to(struct AccountExchangeNote *_AccountExchangeNote, void *_buffer, int offset) {
	int i, shift, new_offset, size;
	
	new_offset = AccountExchangeNote_write(_AccountExchangeNote, _buffer, offset);
	size = new_offset - offset;
	shift = (size > 127) ? 2 : 1;
	for (i = new_offset - 1; i >= offset; -- i)
	    *((char *)_buffer + i + shift) = *((char *)_buffer + i);
	
	write_raw_varint32((unsigned long) size, _buffer, offset);         
	    
	return new_offset + shift;
}

int AccountExchangeNote_read(void *_buffer, struct AccountExchangeNote *_AccountExchangeNote, int offset, int limit) {
	unsigned int i = 0;
	unsigned long long value = i;
	unsigned long tag = value;
	
	/* Reset all attributes to 0 in advance. */
	AccountExchangeNote_clear(_AccountExchangeNote);
	/* Assign the optional attributes. */
	AccountExchangeNote_init_optional_attributes(_AccountExchangeNote);
	
	/* Read/interpret all attributes from buffer offset until upper limit is reached. */
	while(offset < limit) {
	    offset = read_raw_varint32(&tag, _buffer, offset);
		tag = tag>>3;
	    switch(tag){
	        /* tag of: _AccountExchangeNote.msg_type */
	        case 1 :
	        	offset = read_raw_varint32(&tag, _buffer, offset);
	        	_AccountExchangeNote->msg_type = tag;
	        	break;
	        /* tag of: _AccountExchangeNote.billType */
	        case 2 :
	        	offset = read_raw_varint32(&tag, _buffer, offset);
	        	_AccountExchangeNote->billType = tag;
	        	break;
	        /* tag of: _AccountExchangeNote.billId */
	        case 3 :
	        	offset = read_raw_varint32(&tag, _buffer, offset);
	        	_AccountExchangeNote->billId = tag;
	        	break;
	        /* tag of: _AccountExchangeNote.occurTime */
	        case 4 :
	        	offset = read_raw_varint32(&tag, _buffer, offset);
	        	_AccountExchangeNote->occurTime = tag;
	        	break;
	        /* tag of: _AccountExchangeNote._status */
	        case 5 :
	        	offset = read_raw_varint32(&tag, _buffer, offset);
	        	_AccountExchangeNote->status = tag;
	        	break;
	        /* tag of: _AccountExchangeNote._code */
	        case 6 :
	        	offset = read_raw_varint64(&value, _buffer, offset);
	        	_AccountExchangeNote->code = value;
	        	break;
	        /* tag of: _AccountExchangeNote._quality */
	        case 7 :
	        	offset = read_raw_varint32(&tag, _buffer, offset);
	        	_AccountExchangeNote->quality = tag;
	        	break;
	        /* tag of: _AccountExchangeNote._client */
	        case 8 :
	        	/* Re-use 'tag' to store string length. */
	        	offset = read_raw_varint32(&tag, _buffer, offset);
	        	_AccountExchangeNote->_client_len = tag;
	        	for(i = 0; i < tag; ++ i) 
	        	    offset = read_raw_byte((_AccountExchangeNote->client + i), _buffer, offset);
	        	break;
	    }
	}
	
	return offset;
}

int AccountExchangeNote_read_delimited_from(void *_buffer, struct AccountExchangeNote *_AccountExchangeNote, int offset) {
	unsigned long size;
	
	offset = read_raw_varint32(&size, _buffer, offset);
	AccountExchangeNote_read(_buffer, _AccountExchangeNote, offset, size + offset);
	
	return offset + size;
}
