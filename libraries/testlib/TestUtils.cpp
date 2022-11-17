#include "TestUtils.h"

#ifdef _WIN32
    #include <crtdbg.h>
    #include <windows.h>
#endif

namespace testing {
    void MemoryLeakDetector::OnTestStart(const TestInfo&) {
#ifdef _WIN32
    #if defined(_DEBUG) && !defined(IS_MOBILE_PLATFORM)
        _CrtMemCheckpoint(&m_memState);
    #endif
#endif
    }

    void MemoryLeakDetector::OnTestEnd(const TestInfo& test_info) {
        if (test_info.result()->Passed()) {
#ifdef _WIN32
    #if defined(_DEBUG) && !defined(IS_MOBILE_PLATFORM)
            _CrtMemState stateNow, stateDiff;
            _CrtMemCheckpoint(&stateNow);

            const int diffResult = _CrtMemDifference(&stateDiff, &m_memState, &stateNow);
            if (diffResult) {
                FAIL() << "Memory leak of " << stateDiff.lSizes[1] << " byte(s) detected.";
            }
            else {
                SUCCEED() << "No memory leaks found";
            }
    #endif
#endif
        }
    }

    void ResourceLeakDetector::OnTestStart(const TestInfo&) {
#ifdef _WIN32
    #if defined(_DEBUG) && !defined(IS_MOBILE_PLATFORM)
        m_numberOfGuiResources = ::GetGuiResources(::GetCurrentProcess(), GR_GDIOBJECTS);
        m_numberOfUserResources = ::GetGuiResources(::GetCurrentProcess(), GR_USEROBJECTS);
    #endif
#endif
    }

    void ResourceLeakDetector::OnTestEnd(const TestInfo& test_info) {
        if (test_info.result()->Passed()) {
#ifdef _WIN32
    #if defined(_DEBUG) && !defined(IS_MOBILE_PLATFORM)
            const int numberOfGuiResources = ::GetGuiResources(::GetCurrentProcess(), GR_GDIOBJECTS);
            const int numberOfUserResources = ::GetGuiResources(::GetCurrentProcess(), GR_USEROBJECTS);

            std::stringstream sstream;
            std::string message;
            if (numberOfGuiResources != m_numberOfGuiResources) {
                sstream << (numberOfGuiResources - m_numberOfGuiResources) << " leaking GDI resource(s) detected.";
                message = sstream.str();
            }

            sstream.clear();
            if (numberOfUserResources != m_numberOfUserResources) {
                if (!message.empty())
                    message += "\n";
                sstream << (numberOfUserResources - m_numberOfUserResources) << " leaking USER resource(s) detected.";
                message = sstream.str();
            }

            if (!message.empty()) {
                FAIL() << message;
            }
            else {
                SUCCEED() << "No resource leaks found";
            }
    #endif
#endif
        }
    }

    void HandleLeakDetector::OnTestStart(const TestInfo&) {
#ifdef _WIN32
    #if defined(_DEBUG) && !defined(IS_MOBILE_PLATFORM)
        ::GetProcessHandleCount(::GetCurrentProcess(), &m_numberOfProcessHandles);
    #endif
#endif
    }

    void HandleLeakDetector::OnTestEnd(const TestInfo& test_info) {
        if (test_info.result()->Passed()) {
#ifdef _WIN32
    #if defined(_DEBUG) && !defined(IS_MOBILE_PLATFORM)
            DWORD numberOfProcessHandles = 0;
            ::GetProcessHandleCount(::GetCurrentProcess(), &numberOfProcessHandles);
            const int handles = numberOfProcessHandles - m_numberOfProcessHandles;

            if (handles != 0) {
                FAIL() << handles << " leaking handle(s) detected.";
            }
            else {
                SUCCEED() << "No handle leaks found";
            }
    #endif
#endif
        }
    }

    CommandLineParser::CommandLineParser(int argc, char *argv[]) 
        : m_argumentCount(argc) {
        for (int i = 0; i < argc; ++i) {
            m_arguments.push_back(argv[i]);
        }
    }

    int CommandLineParser::argumentCount() const {
        return m_argumentCount;
    }

    std::vector<std::string> CommandLineParser::arguments() const {
        return m_arguments;
    }
}
