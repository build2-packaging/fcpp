#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include <fpp.h>

#undef NDEBUG
#include <assert.h>

struct data
{
  const char* in;  /* Remaining input. */
  char out[1024];
  size_t n;
  int deps;
  int errs;
};

static char* input (char* b, int size, void* u)
{
  struct data* d = (struct data*) u;
  int i = 0;

  if (*d->in == '\0')
    return NULL;

  while (*d->in != '\0' && i < size - 1)
  {
    char c = *d->in++;
    b[i++] = c;
    if (c == '\n')
      break;
  }

  b[i] = '\0';
  return b;
}

static void output (int c, void* u)
{
  struct data* d = (struct data*) u;
  if (d->n < sizeof (d->out) - 1)
    d->out[d->n++] = (char) c;
}

static void error (void* u, char* f, va_list a)
{
  (void) f;
  (void) a;
  ((struct data*) u)->errs++;
}

static void depends (char* f, void* u)
{
  (void) f;
  ((struct data*) u)->deps++;
}

/* Functions are passed to fpp as tag data (void*).
 */
static void* fn (void (*f) (void))
{
  void* r;
  memcpy (&r, &f, sizeof (r));
  return r;
}

static int preprocess (struct data* d, const char* in, char* incdir)
{
  struct fppTag t[16], *p = t;

  memset (d, 0, sizeof (*d));
  d->in = in;

  p->tag = FPPTAG_USERDATA;    p->data = d;                             p++;
  p->tag = FPPTAG_INPUT;       p->data = fn ((void (*) (void)) input);   p++;
  p->tag = FPPTAG_OUTPUT;      p->data = fn ((void (*) (void)) output);  p++;
  p->tag = FPPTAG_ERROR;       p->data = fn ((void (*) (void)) error);   p++;
  p->tag = FPPTAG_DEPENDS;     p->data = fn ((void (*) (void)) depends); p++;
  p->tag = FPPTAG_SHOWVERSION; p->data = (void*) 0;                     p++;
  p->tag = FPPTAG_LINE;        p->data = (void*) 0;                     p++;
  p->tag = FPPTAG_RIGHTCONCAT; p->data = (void*) 1;                     p++;
  p->tag = FPPTAG_INPUT_NAME;  p->data = (void*) "input";               p++;
  p->tag = FPPTAG_INCLUDE_DIR; p->data = incdir;                        p++;
  p->tag = FPPTAG_END;         p->data = NULL;

  return fppPreProcess (t);
}

/* Usage: argv[0] <include-dir>/
 */
int main (int argc, char* argv[])
{
  struct data d;

  assert (argc == 2);

  /* Macro expansion, ## with a number on the left, and an #include that is
   * reported via FPPTAG_DEPENDS.
   */
  assert (preprocess (&d,
                      "#define A 1\n"
                      "int x = A;\n"
                      "#define CAT(a, b) a ## b\n"
                      "float f = CAT(1, .5f);\n"
                      "#include \"include.h\"\n",
                      argv[1]) == 0);
  d.out[d.n] = '\0';
  assert (strstr (d.out, "int x = 1;") != NULL);
  assert (strstr (d.out, "float f = 1.5f;") != NULL);
  assert (strstr (d.out, "int included;") != NULL);
  assert (strchr (d.out, '\x1e') == NULL);
  assert (d.deps == 1 && d.errs == 0);

  /* Diagnostic at the end of input (unterminated #if).
   */
  assert (preprocess (&d, "#if 1\nint a;\n", argv[1]) != 0);
  assert (d.errs != 0);

  /* stdout is still open.
   */
  printf ("ok\n");
  return 0;
}
