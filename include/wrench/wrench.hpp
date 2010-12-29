#ifndef WRENCH_H
#define WRENCH_H

#include "General.hpp"
#include "Math.hpp"
#include "String.hpp"
#include "Console.hpp"
#include "Timer.hpp"

/** Don't use linked stuff */
#ifndef WRENCH_NO_LINKING
#include "Joystick.hpp"
#endif

/** Disable wrench operators in global namespace */
#ifndef WRENCH_NO_GLOBALOPS
#include "GlobalOps.hpp"
#endif

/** Disable short namespace definition */
#ifndef WRENCH_NO_SHORT_NAMESPACE
namespace wr = wrench;
#endif

#endif // WRENCH_H
