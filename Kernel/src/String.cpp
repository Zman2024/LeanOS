#include <String.h>

char strBuffer[0x20];
char hexBuffer[0x20];
char reverseBuffer[0x1000];
char formatBuffer[0x1000];

void reverse(char* str)
{
	nint len = strlen(str);
	nint indexer = 0;

	// return if the string's length is larger then our buffer
	if (len > sizeof(reverseBuffer)) return;

	while (len > 0)
	{
		// store string in buffer in the reverse order
		reverseBuffer[indexer++] = str[--len]; 
	}

	// copy back to itself
	memcpy(str, reverseBuffer, indexer);

	// zero terminate
	str[indexer] = 0;
}

const char* tostr(int64 value, bool sign)
{
	char* str = strBuffer;
	bool isNeg = sign & (value < 0);
	uint64 uvalue = value;

	// return zero correctly
	if (value == 0)
	{
		str[0] = '0';
		str[1] = 0x00;
		return strBuffer;
	}

	// add negitave symbol and switch to positive
	// and set the base to strBuffer + 1
	if (isNeg)
	{
		uvalue = (value * -1);
		str[0] = '-';
		str++;
	}

	// adds characters in the reverse order
	nint index = 0;
	while (uvalue != 0)
	{
		byte digitValue = uvalue % 10;
		uvalue /= 10;
		str[index++] = digitValue + '0';
	}

	// zero terminate the buffer
	str[index] = 0;

	// reverse string from it's base (excluding the minus symbol)
	reverse(str);

	// return buffer from its real base (incl minus)
	return strBuffer;
}

int64 toint(const char* str)
{
	bool negative = (str[0] == '-');
	if (negative) str++;

	uint64 value = 0;
	nint indexer = 0;
	while (str[indexer] != 0)
	{
		value *= 10;
		value += (str[indexer++] - '0');
	}

	if (negative) return -value;
	return value;
}

const char* tohex(uint64 value)
{
	char* str = hexBuffer + 2;

	hexBuffer[0] = '0';
	hexBuffer[1] = 'x';

	// just return "0x00" if it's 0
	if (value == 0x00)
	{
		hexBuffer[2] = '0';
		hexBuffer[3] = '0';
		hexBuffer[4] = 0x00;
		return hexBuffer;
	}

	// add an extra 0 at the beginning if it's less than 0x10
	if (value < 0x10)
	{
		hexBuffer[2] = '0';
		str++;
	}

	nint index = 0;
	while (value != 0)
	{
		// extract lowest 4 bits
		byte digitValue = (value) & 0b00001111;

		// rshift by 4 (divide by 16 or 0x10)
		value >>= 4;

		// if digitvalue is above 9, add the ascii index of ('A' - 10)
		// otherwise just add ascii index of '0'
		digitValue = (digitValue > 9) ? digitValue + ('A' - 10) : digitValue + '0';

		// store in buffer
		str[index++] = digitValue;
	}
	// zero terminate buffer
	str[index] = 0;

	// reverse it from where the numbers start (excl "0x")
	reverse(str);

	// return entire buffer
	return hexBuffer;
}

#pragma region const char* format(char* fstring, i64...)
forceinline void finsert(nint value, char pformat, nint& bufferIndexer)
{
	// the string that we are inserting into the fbuffer
	char* str = nullptr;

	// Convert value to string based on requested format
	switch (pformat)
	{
		// Basic signed integer
		case 0x00:
			str = (char*)tostr(value, true);
			break;

		// Hex string
		case 'x':
		case 'X':
			str = (char*)tohex(value);
			break;

		// Unsigned integer
		case 'u':
		case 'U':
			str = (char*)tostr(value, false);
			break;

		// String pointer
		case 's':
		case 'S':
			str = (char*)value;
			break;

		default:
			bufferIndexer += 3;
			return;
	}

	if (!str) return;

	nint len = strlen(str);
	char* fbase = &formatBuffer[bufferIndexer];
	memcpy(fbase, str, len);
	bufferIndexer += len;
}

// I FUCKING LOVE LEEEEEEEAAAAAN!!!
const char* format(const char* fstring, nint p0, nint p1, nint p2, nint p3, nint p4, nint p5, nint p6, nint p7, nint p8, nint p9)
{
	// the length of the base fstring
	nint fstrlen = strlen(fstring);

	// the current index in the fstring
	nint fstrIndexer = 0;

	// the current index in the buffer
	nint bufferIndexer = 0;

	// a lookup table for the parameters
	nint lookup[10] = {
		p0, p1, p2,
		p3, p4, p5,
		p6, p7, p8,
			p9
	};

	while (fstrIndexer != fstrlen)
	{
		switch (fstring[fstrIndexer])
		{
			case '%':
			{
				char nextChar = fstring[fstrIndexer + 1];
				switch (nextChar)
				{
					// Basic signed integer
					case '0':
					case '1':
					case '2':
					case '3':
					case '4':
					case '5':
					case '6':
					case '7':
					case '8':
					case '9':
						finsert(lookup[nextChar - '0'], 0x00, bufferIndexer);
						fstrIndexer += 2;
						break;

					// Unsigned hex string
					case 'x':
					case 'X':
					{
						nextChar = fstring[fstrIndexer + 2];
						switch (nextChar)
						{
							case '0':
							case '1':
							case '2':
							case '3':
							case '4':
							case '5':
							case '6':
							case '7':
							case '8':
							case '9':
								finsert(lookup[nextChar - '0'], 'x', bufferIndexer);
								fstrIndexer += 3;
								break;

							case 0x00:
							default:
								formatBuffer[bufferIndexer++] = fstring[fstrIndexer++];
								break;
						}
					}
					break;

					// Unsigned integer
					case 'u':
					case 'U':
					{
						nextChar = fstring[fstrIndexer + 2];
						switch (nextChar)
						{
							case '0':
							case '1':
							case '2':
							case '3':
							case '4':
							case '5':
							case '6':
							case '7':
							case '8':
							case '9':
								finsert(lookup[nextChar - '0'], 'u', bufferIndexer);
								fstrIndexer += 3;
								break;

							case 0x00:
							default:
								formatBuffer[bufferIndexer++] = fstring[fstrIndexer++];
								break;
						}
					}
					break;

					// String
					case 's':
					case 'S':
					{
						nextChar = fstring[fstrIndexer + 2];
						switch (nextChar)
						{
							case '0':
							case '1':
							case '2':
							case '3':
							case '4':
							case '5':
							case '6':
							case '7':
							case '8':
							case '9':
								finsert(lookup[nextChar - '0'], 's', bufferIndexer);
								fstrIndexer += 3;
								break;

							case 0x00:
							default:
								formatBuffer[bufferIndexer++] = fstring[fstrIndexer++];
								break;
						}
					}
					break;

					case 0:
					default:
						formatBuffer[bufferIndexer++] = fstring[fstrIndexer++];
						break;
				}
				break;
			}

			default:
				formatBuffer[bufferIndexer++] = fstring[fstrIndexer++];
				break;
		}
	}

	// null terminate
	formatBuffer[bufferIndexer] = 0x00;
	return formatBuffer;

}
#pragma endregion
