#include <stdio.h>
#include <stdint.h>
#include <time.h>

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#else
#include <sys/time.h>
#endif

#include "Diagnostic.h"
#include "FileIO.h"
#include "ParsePrimitives.h"
#include "Util.h"
#include "String.h"

static Char kRandomKeyTable[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

UInt Align(
    UInt Value,
    UInt Alignment
) {
    assert(IsPowerOfTwo(Alignment));

    return (Value + Alignment - 1) & ~(Alignment - 1);
}

Bool IsPowerOfTwo(
    UInt Value
) {
    return (Value & (Value - 1)) == 0;
}

UInt NextPowerOfTwo(UInt Value) {
    Value--;
    Value |= Value >> 1;
    Value |= Value >> 2;
    Value |= Value >> 4;
    Value |= Value >> 8;
    Value |= Value >> 16;
    Value++;
    return Value;
}

Timestamp GetTimestamp() {
	return (Timestamp)time(NULL);
}

Timestamp GetTimestampMs() {
#if defined(_WIN32) || defined(_WIN64)
    FILETIME FileTime;
    ULARGE_INTEGER LargeInt = { 0 };
    GetSystemTimeAsFileTime(&FileTime);
    LargeInt.LowPart = FileTime.dwLowDateTime;
    LargeInt.HighPart = FileTime.dwHighDateTime;

    Timestamp Milliseconds = LargeInt.QuadPart / 10000;
    return Milliseconds - 11644473600000ULL;
#else
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (uint64_t)tv.tv_sec * 1000 + tv.tv_usec / 1000;
#endif
}

Bool GetPlatformErrorMessage(
	CString Buffer,
	Int32 Length
) {
	assert(Buffer);
#if _WIN32
	DWORD MessageID = GetLastError();
	if (!MessageID) return false;
	
	LPSTR MessageBuffer = NULL;
	DWORD MessageLength = FormatMessageA(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		MessageID,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPSTR)&MessageBuffer,
		0,
		NULL
	);

	memcpy_s(Buffer, Length, MessageBuffer, MessageLength);
	LocalFree(MessageBuffer);
#elif defined(__linux__)
    strerror_r(errno, Buffer, Length);
#elif defined(__APPLE__)
    mach_error_t MessageID = errno;
    if (!MessageID) return false;

    Char *MessageBuffer = mach_error_string(MessageID);
    Int64 MessageLength = strlen(MessageBuffer);
    memcpy(Buffer, MessageBuffer, MIN(Length, MessageLength));
#else
    #error "Unsupported Platform"
#endif
    return true;
}

Void GenerateRandomKey(
    CString Buffer,
    Int32 Length
) {
    srand((UInt32)time(NULL));

    for (Int Index = 0; Index < Length; Index++) {
        Buffer[Index] = kRandomKeyTable[rand() % (sizeof(kRandomKeyTable) - 1)];
    }
}

UInt32 SwapUInt32(
    UInt32 Value
) {
    Value = ((Value << 8) & 0xFF00FF00) | ((Value >> 8) & 0xFF00FF);
    return (Value << 16) | (Value >> 16);
}

Int32 Random(Int32* Seed) {
    *Seed = ((*Seed * 1103515245) + 12345) & 0x7fffffff;
    return *Seed;
}

Int32 RandomRange(Int32* Seed, Int32 Min, Int32 Max) {
    Int32 Value = Random(Seed);
    return Min + Value % (Max - Min + 1);
}

Void ReadConfigString(
    CString FilePath,
    CString KeyPath,
    CString Default,
    CString Result,
    Int32 ResultLength
) {
    FileRef File = FileOpen(FilePath);
    if (!File) {
        CStringCopySafe(Result, ResultLength, Default);
        return;
    }

    static UInt8 Data[CONFIG_DATA_BUFFER_SIZE] = { 0 };
    Int32 DataLength = 0;
    if (!FileReadNoAlloc(File, Data, CONFIG_DATA_BUFFER_SIZE, &DataLength)) {
        CStringCopySafe(Result, ResultLength, Default);
        FileClose(File);
        return;
    }

    Char AppName[MAX_PATH] = { 0 };
    Char KeyName[MAX_PATH] = { 0 };
    Char Line[MAX_PATH] = { 0 };
    Int64 AppNameLength = 0;
    CString Cursor = strchr(KeyPath, '.');
    if (Cursor) {
        AppNameLength = Cursor - KeyPath;
        memcpy(AppName, KeyPath, AppNameLength);
        AppName[AppNameLength] = '\0';
    }

    Int64 KeyNameOffset = AppNameLength + 1;
    Int64 KeyNameLength = strlen(KeyPath) - KeyNameOffset;
    memcpy(KeyName, KeyPath + KeyNameOffset, KeyNameLength);
    KeyName[KeyNameLength] = '\0';

    Int32 FoundSection = 0;
    Int32 FoundKey = 0;
    Char* DataBegin = (Char*)Data;
    Char* DataEnd = DataBegin + DataLength;
    while (DataBegin < DataEnd) {
        Char* NewLine = strchr(DataBegin, '\n');
        if (!NewLine) NewLine = DataEnd;

        Int64 LineLength = NewLine - DataBegin;
        if (LineLength > 0 && LineLength < MAX_PATH) {
            strncpy(Line, DataBegin, LineLength);
            Line[LineLength] = '\0';

            Char* Trimmed = Line;
            while (*Trimmed == ' ' || *Trimmed == '\t' || *Trimmed == '\n' || *Trimmed == '\r') Trimmed++;

            if (*Trimmed == '\0' || *Trimmed == ';' || *Trimmed == '#') {
                DataBegin = NewLine + 1;
                continue;
            }

            if (*Trimmed == '[') {
                Char* EndBracket = strchr(Trimmed, ']');
                if (EndBracket) {
                    *EndBracket = '\0';
                    FoundSection = strcmp(Trimmed + 1, AppName) == 0;
                }

                DataBegin = NewLine + 1;
                continue;
            }

            if (FoundSection) {
                Char* Equal = strchr(Trimmed, '=');
                if (Equal) {
                    *Equal = '\0';
                    Char* KeyEnd = Equal - 1;
                    while (*KeyEnd == ' ' || *KeyEnd == '\t') KeyEnd--;
                    *(KeyEnd + 1) = '\0';

                    if (strcmp(Trimmed, KeyName) == 0) {
                        CString Value = Equal + 1;
                        while (*Value == ' ' || *Value == '\t') Value++;

                        Char* ValueEnd = Value + strlen(Value) - 1;
                        while (*ValueEnd == ' ' || *ValueEnd == '\t' || *ValueEnd == '\n' || *ValueEnd == '\r') ValueEnd--;
                        *(ValueEnd + 1) = '\0';

                        CStringCopySafe(Result, ResultLength, Value);
                        FoundKey = 1;
                        break;
                    }
                }
            }
        }

        DataBegin = NewLine + 1;
    }

    if (!FoundKey) {
        CStringCopySafe(Result, ResultLength, Default);
    }

    FileClose(File);
}

Void ReadConfigCharArray(
    CString FilePath,
    CString KeyPath,
    CString Default,
    Char* Result,
    Int32 ResultLength
) {
    ReadConfigString(FilePath, KeyPath, Default, Result, ResultLength);
}

Void ReadConfigBool(
    CString FilePath,
    CString KeyPath,
    CString Default,
    Bool* Result
) {
    Char Buffer[MAX_PATH] = { 0 };
    ReadConfigString(FilePath, KeyPath, Default, Buffer, MAX_PATH);
    ParseBool(Buffer, Result);
}

Void ReadConfigInt8(
    CString FilePath,
    CString KeyPath,
    CString Default,
    Int8* Result
) {
    Char Buffer[MAX_PATH] = { 0 };
    ReadConfigString(FilePath, KeyPath, Default, Buffer, MAX_PATH);
    ParseInt8(Buffer, Result);
}

Void ReadConfigInt16(
    CString FilePath,
    CString KeyPath,
    CString Default,
    Int16* Result
) {
    Char Buffer[MAX_PATH] = { 0 };
    ReadConfigString(FilePath, KeyPath, Default, Buffer, MAX_PATH);
    ParseInt16(Buffer, Result);
}

Void ReadConfigInt32(
    CString FilePath,
    CString KeyPath,
    CString Default,
    Int32* Result
) {
    Char Buffer[MAX_PATH] = { 0 };
    ReadConfigString(FilePath, KeyPath, Default, Buffer, MAX_PATH);
    ParseInt32(Buffer, Result);
}

Void ReadConfigInt64(
    CString FilePath,
    CString KeyPath,
    CString Default,
    Int64* Result
) {
    Char Buffer[MAX_PATH] = { 0 };
    ReadConfigString(FilePath, KeyPath, Default, Buffer, MAX_PATH);
    ParseInt64(Buffer, Result);
}

Void ReadConfigUInt8(
    CString FilePath,
    CString KeyPath,
    CString Default,
    UInt8* Result
) {
    Char Buffer[MAX_PATH] = { 0 };
    ReadConfigString(FilePath, KeyPath, Default, Buffer, MAX_PATH);
    ParseUInt8(Buffer, Result);
}

Void ReadConfigUInt16(
    CString FilePath,
    CString KeyPath,
    CString Default,
    UInt16* Result
) {
    Char Buffer[MAX_PATH] = { 0 };
    ReadConfigString(FilePath, KeyPath, Default, Buffer, MAX_PATH);
    ParseUInt16(Buffer, Result);
}

Void ReadConfigUInt32(
    CString FilePath,
    CString KeyPath,
    CString Default,
    UInt32* Result
) {
    Char Buffer[MAX_PATH] = { 0 };
    ReadConfigString(FilePath, KeyPath, Default, Buffer, MAX_PATH);
    ParseUInt32(Buffer, Result);
}

Void ReadConfigUInt64(
    CString FilePath,
    CString KeyPath,
    CString Default,
    UInt64* Result
) {
    Char Buffer[MAX_PATH] = { 0 };
    ReadConfigString(FilePath, KeyPath, Default, Buffer, MAX_PATH);
    ParseUInt64(Buffer, Result);
}

Void ReadConfigInt(
    CString FilePath,
    CString KeyPath,
    CString Default,
    Int* Result
) {
    Char Buffer[MAX_PATH] = { 0 };
    ReadConfigString(FilePath, KeyPath, Default, Buffer, MAX_PATH);
    ParseInt(Buffer, Result);
}

Timestamp PlatformGetTickCount() {
#ifdef _WIN32
    return GetTickCount64();
#else
    struct timespec ts;

    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (Timestamp)ts.tv_sec * 1000 + ts.tv_nsec / 1000000;
#endif
}

Void PlatformSleep(
    UInt64 Milliseconds
) {
#ifdef _WIN32
    Sleep(Milliseconds);
#else
    struct timespec Remaining = { 0 };
    struct timespec Request = {
        .tv_sec = Milliseconds / 1000,
        .tv_nsec = (Milliseconds % 1000L) * 1000000L,
   };

   nanosleep(&Request, &Remaining);
#endif
}

void __unreachable(const char* message, const char* file, size_t line) {
    exit(EXIT_FAILURE);
}

Void RenderLogo() {
    CString Logo =
        "                                                                                                          \n"
        "                                                                                                          \n"
        "                                                                                                          \n"
        "                 /.                                        /.     .   /.                                  \n"
        "                ///                                       ///    /.  ///                                  \n"
        "               ::::::::.   .:::::'  .:::::.    .:::::.   .::    ::  .::   .:::::.     .:::::.             \n"
        "              ///'  .//:  ///    .//   .//   .//   .//  ///...//.  ///  .//   .//  .//   .//              \n"
        "             :::::  .::' :::    .::::::'    .:::::::'  .::::::.   .::' .::::::'   .::::::'                \n"
        "             '///////'  ///      '///////' //'''''//  //'   .\\\\\\ ///    '///////'  '///////'           \n"
        "                                                                                                          \n"
        "                                                                                                          \n"
        "                                                                                                          \n"
        "                                                                                                          \n"
    ;

    printf("%s", Logo);
}
