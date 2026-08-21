/* Gigatruss typed native math extension for Brainrot stdrot ABI v2. */
#include "stdrot_api.h"
#include <math.h>

static StdrotValue giga_sqrt_impl(StdrotValue *args, int argc)
{
    (void)argc;
    StdrotValue out = {STDROT_DOUBLE, {0}};
    out.val.d = sqrt(args[0].val.d);
    return out;
}

static const StdrotParam giga_sqrt_params[] = {
    {STDROT_DOUBLE, NULL, 0},
};

STDROT_EXPORT_SIG("giga_sqrt", giga_sqrt_impl,
                  ((StdrotParam){STDROT_DOUBLE, NULL, 0}),
                  giga_sqrt_params, 1, 1, false);

static StdrotValue giga_hypot_impl(StdrotValue *args, int argc)
{
    (void)argc;
    StdrotValue out = {STDROT_DOUBLE, {0}};
    out.val.d = hypot(args[0].val.d, args[1].val.d);
    return out;
}

static const StdrotParam giga_hypot_params[] = {
    {STDROT_DOUBLE, NULL, 0},
    {STDROT_DOUBLE, NULL, 0},
};

STDROT_EXPORT_SIG("giga_hypot", giga_hypot_impl,
                  ((StdrotParam){STDROT_DOUBLE, NULL, 0}),
                  giga_hypot_params, 2, 2, false);

static StdrotValue giga_abs_impl(StdrotValue *args, int argc)
{
    (void)argc;
    StdrotValue out = {STDROT_DOUBLE, {0}};
    out.val.d = fabs(args[0].val.d);
    return out;
}

static const StdrotParam giga_abs_params[] = {
    {STDROT_DOUBLE, NULL, 0},
};

STDROT_EXPORT_SIG("giga_abs", giga_abs_impl,
                  ((StdrotParam){STDROT_DOUBLE, NULL, 0}),
                  giga_abs_params, 1, 1, false);
