
/* ./.libs/lt-testdict.c - temporary wrapper executable for .libs/testdict
   Generated by ltmain.sh (GNU libtool) 2.2.6b

   The testdict program cannot be directly executed until all the libtool
   libraries that it depends on are installed.

   This wrapper executable should never be moved out of the build directory.
   If it is, it will not operate correctly.

   Currently, it simply execs the wrapper *script* "/bin/sh testdict",
   but could eventually absorb all of the scripts functionality and
   exec .libs/testdict directly.
*/
#include <stdio.h>
#include <stdlib.h>
#ifdef _MSC_VER
# include <direct.h>
# include <process.h>
# include <io.h>
# define setmode _setmode
#else
# include <unistd.h>
# include <stdint.h>
# ifdef __CYGWIN__
#  include <io.h>
#  define HAVE_SETENV
#  ifdef __STRICT_ANSI__
char *realpath (const char *, char *);
int putenv (char *);
int setenv (const char *, const char *, int);
#  endif
# endif
#endif
#include <malloc.h>
#include <stdarg.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>

#if defined(PATH_MAX)
# define LT_PATHMAX PATH_MAX
#elif defined(MAXPATHLEN)
# define LT_PATHMAX MAXPATHLEN
#else
# define LT_PATHMAX 1024
#endif

#ifndef S_IXOTH
# define S_IXOTH 0
#endif
#ifndef S_IXGRP
# define S_IXGRP 0
#endif

#ifdef _MSC_VER
# define S_IXUSR _S_IEXEC
# define stat _stat
# ifndef _INTPTR_T_DEFINED
#  define intptr_t int
# endif
#endif

#ifndef DIR_SEPARATOR
# define DIR_SEPARATOR '/'
# define PATH_SEPARATOR ':'
#endif

#if defined (_WIN32) || defined (__MSDOS__) || defined (__DJGPP__) || \
  defined (__OS2__)
# define HAVE_DOS_BASED_FILE_SYSTEM
# define FOPEN_WB "wb"
# ifndef DIR_SEPARATOR_2
#  define DIR_SEPARATOR_2 '\\'
# endif
# ifndef PATH_SEPARATOR_2
#  define PATH_SEPARATOR_2 ';'
# endif
#endif

#ifndef DIR_SEPARATOR_2
# define IS_DIR_SEPARATOR(ch) ((ch) == DIR_SEPARATOR)
#else /* DIR_SEPARATOR_2 */
# define IS_DIR_SEPARATOR(ch) \
	(((ch) == DIR_SEPARATOR) || ((ch) == DIR_SEPARATOR_2))
#endif /* DIR_SEPARATOR_2 */

#ifndef PATH_SEPARATOR_2
# define IS_PATH_SEPARATOR(ch) ((ch) == PATH_SEPARATOR)
#else /* PATH_SEPARATOR_2 */
# define IS_PATH_SEPARATOR(ch) ((ch) == PATH_SEPARATOR_2)
#endif /* PATH_SEPARATOR_2 */

#ifdef __CYGWIN__
# define FOPEN_WB "wb"
#endif

#ifndef FOPEN_WB
# define FOPEN_WB "w"
#endif
#ifndef _O_BINARY
# define _O_BINARY 0
#endif

#define XMALLOC(type, num)      ((type *) xmalloc ((num) * sizeof(type)))
#define XFREE(stale) do { \
  if (stale) { free ((void *) stale); stale = 0; } \
} while (0)

#undef LTWRAPPER_DEBUGPRINTF
#if defined DEBUGWRAPPER
# define LTWRAPPER_DEBUGPRINTF(args) ltwrapper_debugprintf args
static void
ltwrapper_debugprintf (const char *fmt, ...)
{
    va_list args;
    va_start (args, fmt);
    (void) vfprintf (stderr, fmt, args);
    va_end (args);
}
#else
# define LTWRAPPER_DEBUGPRINTF(args)
#endif

const char *program_name = NULL;

void *xmalloc (size_t num);
char *xstrdup (const char *string);
const char *base_name (const char *name);
char *find_executable (const char *wrapper);
char *chase_symlinks (const char *pathspec);
int make_executable (const char *path);
int check_executable (const char *path);
char *strendzap (char *str, const char *pat);
void lt_fatal (const char *message, ...);
void lt_setenv (const char *name, const char *value);
char *lt_extend_str (const char *orig_value, const char *add, int to_end);
void lt_opt_process_env_set (const char *arg);
void lt_opt_process_env_prepend (const char *arg);
void lt_opt_process_env_append (const char *arg);
int lt_split_name_value (const char *arg, char** name, char** value);
void lt_update_exe_path (const char *name, const char *value);
void lt_update_lib_path (const char *name, const char *value);

static const char *script_text_part1 =
  "#! /bin/sh\n"
  "\n"
  "# testdict - temporary wrapper script for .libs/testdict\n"
  "# Generated by ltmain.sh (GNU libtool) 2.2.6b\n"
  "#\n"
  "# The testdict program cannot be directly executed until all the libtool\n"
  "# libraries that it depends on are installed.\n"
  "#\n"
  "# This wrapper script should never be moved out of the build directory.\n"
  "# If it is, it will not operate correctly.\n"
  "\n"
  "# Sed substitution that helps us do robust quoting.  It backslashifies\n"
  "# metacharacters that are still active within double-quoted strings.\n"
  "Xsed='/usr/bin/sed -e 1s/^X//'\n"
  "sed_quote_subst='s/\\([`\"$\\\\]\\)/\\\\\\1/g'\n"
  "\n"
  "# Be Bourne compatible\n"
  "if test -n \"${ZSH_VERSION+set}\" && (emulate sh) >/dev/null 2>&1; then\n"
  "  emulate sh\n"
  "  NULLCMD=:\n"
  "  # Zsh 3.x and 4.x performs word splitting on ${1+\"$@\"}, which\n"
  "  # is contrary to our usage.  Disable this feature.\n"
  "  alias -g '${1+\"$@\"}'='\"$@\"'\n"
  "  setopt NO_GLOB_SUBST\n"
  "else\n"
  "  case `(set -o) 2>/dev/null` in *posix*) set -o posix;; esac\n"
  "fi\n"
  "BIN_SH=xpg4; export BIN_SH # for Tru64\n"
  "DUALCASE=1; export DUALCASE # for MKS sh\n"
  "\n"
  "# The HP-UX ksh and POSIX shell print the target directory to stdout\n"
  "# if CDPATH is set.\n"
  "(unset CDPATH) >/dev/null 2>&1 && unset CDPATH\n"
  "\n"
  "relink_command=\"\"\n"
  "\n"
  "# This environment variable determines our operation mode.\n"
  "if test \"$libtool_install_magic\" = \"%%%MAGIC variable%%%\"; then\n"
  "  # install mode needs the following variables:\n"
  "  generated_by_libtool_version='2.2.6b'\n"
  "  notinst_deplibs=' ./libxml2.la /usr/lib/libiconv.la'\n"
  "else\n"
  "  # When we are sourced in execute mode, $file and $ECHO are already set.\n"
  "  if test \"$libtool_execute_magic\" != \"%%%MAGIC variable%%%\"; then\n"
  "    ECHO=\"echo\"\n"
  "    file=\"$0\"\n"
  "    # Make sure echo works.\n"
  "    if test \"X$1\" = X--no-reexec; then\n"
  "      # Discard the --no-reexec flag, and continue.\n"
  "      shift\n"
  "    elif test \"X`{ $ECHO '\\t'; } 2>/dev/null`\" = 'X\\t'; then\n"
  "      # Yippee, $ECHO works!\n"
  "      :\n"
  "    else\n"
  "      # Restart under the correct shell, and then maybe $ECHO will work.\n"
  "      exec /bin/sh \"$0\" --no-reexec ${1+\"$@\"}\n"
  "    fi\n"
  "  fi\n"
  "\n"
  "  # Find the directory that this script lives in.\n"
  "  thisdir=`$ECHO \"X$file\" | $Xsed -e 's%/[^/]*$%%'`\n"
  "  test \"x$thisdir\" = \"x$file\" && thisdir=.\n"
  "\n"
  "  # Follow symbolic links until we get to the real thisdir.\n"
  "  file=`ls -ld \"$file\" | /usr/bin/sed -n 's/.*-> //p'`\n"
  "  while test -n \"$file\"; do\n"
  "    destdir=`$ECHO \"X$file\" | $Xsed -e 's%/[^/]*$%%'`\n"
  "\n"
  "    # If there was a directory component, then change thisdir.\n"
  "    if test \"x$destdir\" != \"x$file\"; then\n"
  "      case \"$destdir\" in\n"
  "      [\\\\/]* | [A-Za-z]:[\\\\/]*) thisdir=\"$destdir\" ;;\n"
  "      *) thisdir=\"$thisdir/$destdir\" ;;\n"
  "      esac\n"
  "    fi\n"
  "\n"
  "    file=`$ECHO \"X$file\" | $Xsed -e 's%^.*/%%'`\n"
  "    file=`ls -ld \"$thisdir/$file\" | /usr/bin/sed -n 's/.*-> //p'`\n"
  "  done\n"
  "\n"
;

static const char *script_text_part2 =
  "\n"
  "  # Usually 'no', except on cygwin/mingw when embedded into\n"
  "  # the cwrapper.\n"
  "  WRAPPER_SCRIPT_BELONGS_IN_OBJDIR=yes\n"
  "  if test \"$WRAPPER_SCRIPT_BELONGS_IN_OBJDIR\" = \"yes\"; then\n"
  "    # special case for '.'\n"
  "    if test \"$thisdir\" = \".\"; then\n"
  "      thisdir=`pwd`\n"
  "    fi\n"
  "    # remove .libs from thisdir\n"
  "    case \"$thisdir\" in\n"
  "    *[\\\\/].libs ) thisdir=`$ECHO \"X$thisdir\" | $Xsed -e 's%[\\\\/][^\\\\/]*$%%'` ;;\n"
  "    .libs )   thisdir=. ;;\n"
  "    esac\n"
  "  fi\n"
  "\n"
  "  # Try to get the absolute directory name.\n"
  "  absdir=`cd \"$thisdir\" && pwd`\n"
  "  test -n \"$absdir\" && thisdir=\"$absdir\"\n"
  "\n"
  "  program='testdict'\n"
  "  progdir=\"$thisdir/.libs\"\n"
  "\n"
  "\n"
  "  if test -f \"$progdir/$program\"; then\n"
  "    # Add our own library path to PATH\n"
  "    PATH=\"/cygdrive/e/buildlibxml2/jni/libxml2/.libs:/usr/lib:$PATH\"\n"
  "\n"
  "    # Some systems cannot cope with colon-terminated PATH\n"
  "    # The second colon is a workaround for a bug in BeOS R4 sed\n"
  "    PATH=`$ECHO \"X$PATH\" | $Xsed -e 's/::*$//'`\n"
  "\n"
  "    export PATH\n"
  "\n"
  "    # Add the dll search path components to the executable PATH\n"
  "    PATH=/cygdrive/e/buildlibxml2/jni/libxml2/.libs:/usr/local/lib:/usr/local/bin:$PATH\n"
  "\n"
  "    if test \"$libtool_execute_magic\" != \"%%%MAGIC variable%%%\"; then\n"
  "      # Run the actual program with our arguments.\n"
  "\n"
  "      exec \"$progdir/$program\" ${1+\"$@\"}\n"
  "\n"
  "      $ECHO \"$0: cannot exec $program $*\" 1>&2\n"
  "      exit 1\n"
  "    fi\n"
  "  else\n"
  "    # The program doesn't exist.\n"
  "    $ECHO \"$0: error: \\`$progdir/$program' does not exist\" 1>&2\n"
  "    $ECHO \"This script is just a wrapper for $program.\" 1>&2\n"
  "    echo \"See the libtool documentation for more information.\" 1>&2\n"
  "    exit 1\n"
  "  fi\n"
  "fi\n"
;
const char * MAGIC_EXE = "%%%MAGIC EXE variable%%%";
const char * LIB_PATH_VARNAME = "PATH";
const char * LIB_PATH_VALUE   = "/cygdrive/e/buildlibxml2/jni/libxml2/.libs:/usr/lib:";
const char * EXE_PATH_VARNAME = "PATH";
const char * EXE_PATH_VALUE   = "/cygdrive/e/buildlibxml2/jni/libxml2/.libs:/usr/local/lib:/usr/local/bin:";
const char * TARGET_PROGRAM_NAME = "testdict"; /* hopefully, no .exe */

#define LTWRAPPER_OPTION_PREFIX         "--lt-"
#define LTWRAPPER_OPTION_PREFIX_LENGTH  5

static const size_t opt_prefix_len         = LTWRAPPER_OPTION_PREFIX_LENGTH;
static const char *ltwrapper_option_prefix = LTWRAPPER_OPTION_PREFIX;

static const char *dumpscript_opt       = LTWRAPPER_OPTION_PREFIX "dump-script";

static const size_t env_set_opt_len     = LTWRAPPER_OPTION_PREFIX_LENGTH + 7;
static const char *env_set_opt          = LTWRAPPER_OPTION_PREFIX "env-set";
  /* argument is putenv-style "foo=bar", value of foo is set to bar */

static const size_t env_prepend_opt_len = LTWRAPPER_OPTION_PREFIX_LENGTH + 11;
static const char *env_prepend_opt      = LTWRAPPER_OPTION_PREFIX "env-prepend";
  /* argument is putenv-style "foo=bar", new value of foo is bar${foo} */

static const size_t env_append_opt_len  = LTWRAPPER_OPTION_PREFIX_LENGTH + 10;
static const char *env_append_opt       = LTWRAPPER_OPTION_PREFIX "env-append";
  /* argument is putenv-style "foo=bar", new value of foo is ${foo}bar */

int
main (int argc, char *argv[])
{
  char **newargz;
  int  newargc;
  char *tmp_pathspec;
  char *actual_cwrapper_path;
  char *actual_cwrapper_name;
  char *target_name;
  char *lt_argv_zero;
  intptr_t rval = 127;

  int i;

  program_name = (char *) xstrdup (base_name (argv[0]));
  LTWRAPPER_DEBUGPRINTF (("(main) argv[0]      : %s\n", argv[0]));
  LTWRAPPER_DEBUGPRINTF (("(main) program_name : %s\n", program_name));

  /* very simple arg parsing; don't want to rely on getopt */
  for (i = 1; i < argc; i++)
    {
      if (strcmp (argv[i], dumpscript_opt) == 0)
	{
          setmode(1,_O_BINARY);
	  printf ("%s", script_text_part1);
	  printf ("%s", script_text_part2);
	  return 0;
	}
    }

  newargz = XMALLOC (char *, argc + 1);
  tmp_pathspec = find_executable (argv[0]);
  if (tmp_pathspec == NULL)
    lt_fatal ("Couldn't find %s", argv[0]);
  LTWRAPPER_DEBUGPRINTF (("(main) found exe (before symlink chase) at : %s\n",
			  tmp_pathspec));

  actual_cwrapper_path = chase_symlinks (tmp_pathspec);
  LTWRAPPER_DEBUGPRINTF (("(main) found exe (after symlink chase) at : %s\n",
			  actual_cwrapper_path));
  XFREE (tmp_pathspec);

  actual_cwrapper_name = xstrdup( base_name (actual_cwrapper_path));
  strendzap (actual_cwrapper_path, actual_cwrapper_name);

  /* wrapper name transforms */
  strendzap (actual_cwrapper_name, ".exe");
  tmp_pathspec = lt_extend_str (actual_cwrapper_name, ".exe", 1);
  XFREE (actual_cwrapper_name);
  actual_cwrapper_name = tmp_pathspec;
  tmp_pathspec = 0;

  /* target_name transforms -- use actual target program name; might have lt- prefix */
  target_name = xstrdup (base_name (TARGET_PROGRAM_NAME));
  strendzap (target_name, ".exe");
  tmp_pathspec = lt_extend_str (target_name, ".exe", 1);
  XFREE (target_name);
  target_name = tmp_pathspec;
  tmp_pathspec = 0;

  LTWRAPPER_DEBUGPRINTF (("(main) libtool target name: %s\n",
			  target_name));
  newargz[0] =
    XMALLOC (char, (strlen (actual_cwrapper_path) +
		    strlen (".libs") + 1 + strlen (actual_cwrapper_name) + 1));
  strcpy (newargz[0], actual_cwrapper_path);
  strcat (newargz[0], ".libs");
  strcat (newargz[0], "/");
  /* stop here, and copy so we don't have to do this twice */
  tmp_pathspec = xstrdup (newargz[0]);

  /* do NOT want the lt- prefix here, so use actual_cwrapper_name */
  strcat (newargz[0], actual_cwrapper_name);

  /* DO want the lt- prefix here if it exists, so use target_name */
  lt_argv_zero = lt_extend_str (tmp_pathspec, target_name, 1);
  XFREE (tmp_pathspec);
  tmp_pathspec = NULL;
  XFREE (target_name);
  XFREE (actual_cwrapper_path);
  XFREE (actual_cwrapper_name);

  lt_setenv ("BIN_SH", "xpg4"); /* for Tru64 */
  lt_setenv ("DUALCASE", "1");  /* for MSK sh */
  lt_update_lib_path (LIB_PATH_VARNAME, LIB_PATH_VALUE);
  lt_update_exe_path (EXE_PATH_VARNAME, EXE_PATH_VALUE);

  newargc=0;
  for (i = 1; i < argc; i++)
    {
      if (strncmp (argv[i], env_set_opt, env_set_opt_len) == 0)
        {
          if (argv[i][env_set_opt_len] == '=')
            {
              const char *p = argv[i] + env_set_opt_len + 1;
              lt_opt_process_env_set (p);
            }
          else if (argv[i][env_set_opt_len] == '\0' && i + 1 < argc)
            {
              lt_opt_process_env_set (argv[++i]); /* don't copy */
            }
          else
            lt_fatal ("%s missing required argument", env_set_opt);
          continue;
        }
      if (strncmp (argv[i], env_prepend_opt, env_prepend_opt_len) == 0)
        {
          if (argv[i][env_prepend_opt_len] == '=')
            {
              const char *p = argv[i] + env_prepend_opt_len + 1;
              lt_opt_process_env_prepend (p);
            }
          else if (argv[i][env_prepend_opt_len] == '\0' && i + 1 < argc)
            {
              lt_opt_process_env_prepend (argv[++i]); /* don't copy */
            }
          else
            lt_fatal ("%s missing required argument", env_prepend_opt);
          continue;
        }
      if (strncmp (argv[i], env_append_opt, env_append_opt_len) == 0)
        {
          if (argv[i][env_append_opt_len] == '=')
            {
              const char *p = argv[i] + env_append_opt_len + 1;
              lt_opt_process_env_append (p);
            }
          else if (argv[i][env_append_opt_len] == '\0' && i + 1 < argc)
            {
              lt_opt_process_env_append (argv[++i]); /* don't copy */
            }
          else
            lt_fatal ("%s missing required argument", env_append_opt);
          continue;
        }
      if (strncmp (argv[i], ltwrapper_option_prefix, opt_prefix_len) == 0)
        {
          /* however, if there is an option in the LTWRAPPER_OPTION_PREFIX
             namespace, but it is not one of the ones we know about and
             have already dealt with, above (inluding dump-script), then
             report an error. Otherwise, targets might begin to believe
             they are allowed to use options in the LTWRAPPER_OPTION_PREFIX
             namespace. The first time any user complains about this, we'll
             need to make LTWRAPPER_OPTION_PREFIX a configure-time option
             or a configure.ac-settable value.
           */
          lt_fatal ("Unrecognized option in %s namespace: '%s'",
                    ltwrapper_option_prefix, argv[i]);
        }
      /* otherwise ... */
      newargz[++newargc] = xstrdup (argv[i]);
    }
  newargz[++newargc] = NULL;

  LTWRAPPER_DEBUGPRINTF     (("(main) lt_argv_zero : %s\n", (lt_argv_zero ? lt_argv_zero : "<NULL>")));
  for (i = 0; i < newargc; i++)
    {
      LTWRAPPER_DEBUGPRINTF (("(main) newargz[%d]   : %s\n", i, (newargz[i] ? newargz[i] : "<NULL>")));
    }

  execv (lt_argv_zero, newargz);
  return rval; /* =127, but avoids unused variable warning */
}

void *
xmalloc (size_t num)
{
  void *p = (void *) malloc (num);
  if (!p)
    lt_fatal ("Memory exhausted");

  return p;
}

char *
xstrdup (const char *string)
{
  return string ? strcpy ((char *) xmalloc (strlen (string) + 1),
			  string) : NULL;
}

const char *
base_name (const char *name)
{
  const char *base;

#if defined (HAVE_DOS_BASED_FILE_SYSTEM)
  /* Skip over the disk name in MSDOS pathnames. */
  if (isalpha ((unsigned char) name[0]) && name[1] == ':')
    name += 2;
#endif

  for (base = name; *name; name++)
    if (IS_DIR_SEPARATOR (*name))
      base = name + 1;
  return base;
}

int
check_executable (const char *path)
{
  struct stat st;

  LTWRAPPER_DEBUGPRINTF (("(check_executable)  : %s\n",
			  path ? (*path ? path : "EMPTY!") : "NULL!"));
  if ((!path) || (!*path))
    return 0;

  if ((stat (path, &st) >= 0)
      && (st.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH)))
    return 1;
  else
    return 0;
}

int
make_executable (const char *path)
{
  int rval = 0;
  struct stat st;

  LTWRAPPER_DEBUGPRINTF (("(make_executable)   : %s\n",
			  path ? (*path ? path : "EMPTY!") : "NULL!"));
  if ((!path) || (!*path))
    return 0;

  if (stat (path, &st) >= 0)
    {
      rval = chmod (path, st.st_mode | S_IXOTH | S_IXGRP | S_IXUSR);
    }
  return rval;
}

/* Searches for the full path of the wrapper.  Returns
   newly allocated full path name if found, NULL otherwise
   Does not chase symlinks, even on platforms that support them.
*/
char *
find_executable (const char *wrapper)
{
  int has_slash = 0;
  const char *p;
  const char *p_next;
  /* static buffer for getcwd */
  char tmp[LT_PATHMAX + 1];
  int tmp_len;
  char *concat_name;

  LTWRAPPER_DEBUGPRINTF (("(find_executable)   : %s\n",
			  wrapper ? (*wrapper ? wrapper : "EMPTY!") : "NULL!"));

  if ((wrapper == NULL) || (*wrapper == '\0'))
    return NULL;

  /* Absolute path? */
#if defined (HAVE_DOS_BASED_FILE_SYSTEM)
  if (isalpha ((unsigned char) wrapper[0]) && wrapper[1] == ':')
    {
      concat_name = xstrdup (wrapper);
      if (check_executable (concat_name))
	return concat_name;
      XFREE (concat_name);
    }
  else
    {
#endif
      if (IS_DIR_SEPARATOR (wrapper[0]))
	{
	  concat_name = xstrdup (wrapper);
	  if (check_executable (concat_name))
	    return concat_name;
	  XFREE (concat_name);
	}
#if defined (HAVE_DOS_BASED_FILE_SYSTEM)
    }
#endif

  for (p = wrapper; *p; p++)
    if (*p == '/')
      {
	has_slash = 1;
	break;
      }
  if (!has_slash)
    {
      /* no slashes; search PATH */
      const char *path = getenv ("PATH");
      if (path != NULL)
	{
	  for (p = path; *p; p = p_next)
	    {
	      const char *q;
	      size_t p_len;
	      for (q = p; *q; q++)
		if (IS_PATH_SEPARATOR (*q))
		  break;
	      p_len = q - p;
	      p_next = (*q == '\0' ? q : q + 1);
	      if (p_len == 0)
		{
		  /* empty path: current directory */
		  if (getcwd (tmp, LT_PATHMAX) == NULL)
		    lt_fatal ("getcwd failed");
		  tmp_len = strlen (tmp);
		  concat_name =
		    XMALLOC (char, tmp_len + 1 + strlen (wrapper) + 1);
		  memcpy (concat_name, tmp, tmp_len);
		  concat_name[tmp_len] = '/';
		  strcpy (concat_name + tmp_len + 1, wrapper);
		}
	      else
		{
		  concat_name =
		    XMALLOC (char, p_len + 1 + strlen (wrapper) + 1);
		  memcpy (concat_name, p, p_len);
		  concat_name[p_len] = '/';
		  strcpy (concat_name + p_len + 1, wrapper);
		}
	      if (check_executable (concat_name))
		return concat_name;
	      XFREE (concat_name);
	    }
	}
      /* not found in PATH; assume curdir */
    }
  /* Relative path | not found in path: prepend cwd */
  if (getcwd (tmp, LT_PATHMAX) == NULL)
    lt_fatal ("getcwd failed");
  tmp_len = strlen (tmp);
  concat_name = XMALLOC (char, tmp_len + 1 + strlen (wrapper) + 1);
  memcpy (concat_name, tmp, tmp_len);
  concat_name[tmp_len] = '/';
  strcpy (concat_name + tmp_len + 1, wrapper);

  if (check_executable (concat_name))
    return concat_name;
  XFREE (concat_name);
  return NULL;
}

char *
chase_symlinks (const char *pathspec)
{
#ifndef S_ISLNK
  return xstrdup (pathspec);
#else
  char buf[LT_PATHMAX];
  struct stat s;
  char *tmp_pathspec = xstrdup (pathspec);
  char *p;
  int has_symlinks = 0;
  while (strlen (tmp_pathspec) && !has_symlinks)
    {
      LTWRAPPER_DEBUGPRINTF (("checking path component for symlinks: %s\n",
			      tmp_pathspec));
      if (lstat (tmp_pathspec, &s) == 0)
	{
	  if (S_ISLNK (s.st_mode) != 0)
	    {
	      has_symlinks = 1;
	      break;
	    }

	  /* search backwards for last DIR_SEPARATOR */
	  p = tmp_pathspec + strlen (tmp_pathspec) - 1;
	  while ((p > tmp_pathspec) && (!IS_DIR_SEPARATOR (*p)))
	    p--;
	  if ((p == tmp_pathspec) && (!IS_DIR_SEPARATOR (*p)))
	    {
	      /* no more DIR_SEPARATORS left */
	      break;
	    }
	  *p = '\0';
	}
      else
	{
	  char *errstr = strerror (errno);
	  lt_fatal ("Error accessing file %s (%s)", tmp_pathspec, errstr);
	}
    }
  XFREE (tmp_pathspec);

  if (!has_symlinks)
    {
      return xstrdup (pathspec);
    }

  tmp_pathspec = realpath (pathspec, buf);
  if (tmp_pathspec == 0)
    {
      lt_fatal ("Could not follow symlinks for %s", pathspec);
    }
  return xstrdup (tmp_pathspec);
#endif
}

char *
strendzap (char *str, const char *pat)
{
  size_t len, patlen;

  assert (str != NULL);
  assert (pat != NULL);

  len = strlen (str);
  patlen = strlen (pat);

  if (patlen <= len)
    {
      str += len - patlen;
      if (strcmp (str, pat) == 0)
	*str = '\0';
    }
  return str;
}

static void
lt_error_core (int exit_status, const char *mode,
	       const char *message, va_list ap)
{
  fprintf (stderr, "%s: %s: ", program_name, mode);
  vfprintf (stderr, message, ap);
  fprintf (stderr, ".\n");

  if (exit_status >= 0)
    exit (exit_status);
}

void
lt_fatal (const char *message, ...)
{
  va_list ap;
  va_start (ap, message);
  lt_error_core (EXIT_FAILURE, "FATAL", message, ap);
  va_end (ap);
}

void
lt_setenv (const char *name, const char *value)
{
  LTWRAPPER_DEBUGPRINTF (("(lt_setenv) setting '%s' to '%s'\n",
                          (name ? name : "<NULL>"),
                          (value ? value : "<NULL>")));
  {
#ifdef HAVE_SETENV
    /* always make a copy, for consistency with !HAVE_SETENV */
    char *str = xstrdup (value);
    setenv (name, str, 1);
#else
    int len = strlen (name) + 1 + strlen (value) + 1;
    char *str = XMALLOC (char, len);
    sprintf (str, "%s=%s", name, value);
    if (putenv (str) != EXIT_SUCCESS)
      {
        XFREE (str);
      }
#endif
  }
}

char *
lt_extend_str (const char *orig_value, const char *add, int to_end)
{
  char *new_value;
  if (orig_value && *orig_value)
    {
      int orig_value_len = strlen (orig_value);
      int add_len = strlen (add);
      new_value = XMALLOC (char, add_len + orig_value_len + 1);
      if (to_end)
        {
          strcpy (new_value, orig_value);
          strcpy (new_value + orig_value_len, add);
        }
      else
        {
          strcpy (new_value, add);
          strcpy (new_value + add_len, orig_value);
        }
    }
  else
    {
      new_value = xstrdup (add);
    }
  return new_value;
}

int
lt_split_name_value (const char *arg, char** name, char** value)
{
  const char *p;
  int len;
  if (!arg || !*arg)
    return 1;

  p = strchr (arg, (int)'=');

  if (!p)
    return 1;

  *value = xstrdup (++p);

  len = strlen (arg) - strlen (*value);
  *name = XMALLOC (char, len);
  strncpy (*name, arg, len-1);
  (*name)[len - 1] = '\0';

  return 0;
}

void
lt_opt_process_env_set (const char *arg)
{
  char *name = NULL;
  char *value = NULL;

  if (lt_split_name_value (arg, &name, &value) != 0)
    {
      XFREE (name);
      XFREE (value);
      lt_fatal ("bad argument for %s: '%s'", env_set_opt, arg);
    }

  lt_setenv (name, value);
  XFREE (name);
  XFREE (value);
}

void
lt_opt_process_env_prepend (const char *arg)
{
  char *name = NULL;
  char *value = NULL;
  char *new_value = NULL;

  if (lt_split_name_value (arg, &name, &value) != 0)
    {
      XFREE (name);
      XFREE (value);
      lt_fatal ("bad argument for %s: '%s'", env_prepend_opt, arg);
    }

  new_value = lt_extend_str (getenv (name), value, 0);
  lt_setenv (name, new_value);
  XFREE (new_value);
  XFREE (name);
  XFREE (value);
}

void
lt_opt_process_env_append (const char *arg)
{
  char *name = NULL;
  char *value = NULL;
  char *new_value = NULL;

  if (lt_split_name_value (arg, &name, &value) != 0)
    {
      XFREE (name);
      XFREE (value);
      lt_fatal ("bad argument for %s: '%s'", env_append_opt, arg);
    }

  new_value = lt_extend_str (getenv (name), value, 1);
  lt_setenv (name, new_value);
  XFREE (new_value);
  XFREE (name);
  XFREE (value);
}

void
lt_update_exe_path (const char *name, const char *value)
{
  LTWRAPPER_DEBUGPRINTF (("(lt_update_exe_path) modifying '%s' by prepending '%s'\n",
                          (name ? name : "<NULL>"),
                          (value ? value : "<NULL>")));

  if (name && *name && value && *value)
    {
      char *new_value = lt_extend_str (getenv (name), value, 0);
      /* some systems can't cope with a ':'-terminated path #' */
      int len = strlen (new_value);
      while (((len = strlen (new_value)) > 0) && IS_PATH_SEPARATOR (new_value[len-1]))
        {
          new_value[len-1] = '\0';
        }
      lt_setenv (name, new_value);
      XFREE (new_value);
    }
}

void
lt_update_lib_path (const char *name, const char *value)
{
  LTWRAPPER_DEBUGPRINTF (("(lt_update_lib_path) modifying '%s' by prepending '%s'\n",
                          (name ? name : "<NULL>"),
                          (value ? value : "<NULL>")));

  if (name && *name && value && *value)
    {
      char *new_value = lt_extend_str (getenv (name), value, 0);
      lt_setenv (name, new_value);
      XFREE (new_value);
    }
}


