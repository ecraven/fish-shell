/** \file path.h

	Directory utilities. This library contains functions for locating
	configuration directories, for testing if a command with a given
	name can be found in the PATH, and various other path-related
	issues.
*/

#ifndef FISH_PATH_H
#define FISH_PATH_H

/**
   Return value for path_cdpath_get when locatied a rotten symlink
 */
#define EROTTEN 1

/**
   Returns the user configuration directory for fish. If the directory
   or one of it's parents doesn't exist, they are first created.

   \param path The directory as an out param
   \return whether the directory was returned successfully
*/
bool path_get_config(wcstring &path);

/**
   Finds the full path of an executable in a newly allocated string.
   
   \param cmd The name of the executable.
   \return 0 if the command can not be found, the path of the command otherwise. The result should be freed with free().
*/
wchar_t *path_get_path( const wchar_t *cmd );

/** Returns whether the path can be used for an implicit cd command; if so, also returns the path by reference (if desired). This requires it to start with one of the allowed prefixes (., .., ~) and resolve to a directory. */
bool path_can_be_implicit_cd(const wcstring &path, wcstring *out_path = NULL, const wchar_t *wd = NULL);

class env_vars;
bool path_get_path_string(const wcstring &cmd, wcstring &output);
bool path_get_path_string(const wcstring &cmd, wcstring &output, const env_vars &vars);

/**
   Returns the full path of the specified directory, using the CDPATH
   variable as a list of base directories for relative paths. The
   returned string is allocated using halloc and the specified
   context.
   
   If no valid path is found, null is returned and errno is set to
   ENOTDIR if at least one such path was found, but it did not point
   to a directory, EROTTEN if a arotten symbolic link was found, or
   ENOENT if no file of the specified name was found. If both a rotten
   symlink and a file are found, it is undefined which error status
   will be returned.
   
   \param in The name of the directory.
   \param wd The working directory, or NULL to use the default. The working directory should have a slash appended at the end.
   \return 0 if the command can not be found, the path of the command otherwise. The path should be free'd with free().
*/

wchar_t *path_allocate_cdpath( const wcstring &in, const wchar_t *wd = NULL);
bool path_can_get_cdpath(const wcstring &in, const wchar_t *wd = NULL);
bool path_get_cdpath_string(const wcstring &in, wcstring &out, const env_vars &vars);

/**
   Remove double slashes and trailing slashes from a path,
   e.g. transform foo//bar/ into foo/bar. The string is modified in-place.
 */
void path_make_canonical( wcstring &path );

bool path_is_valid(const wcstring &path, const wcstring &working_directory);

/** Returns whether the two paths refer to the same file */
bool paths_are_same_file(const wcstring &path1, const wcstring &path2);

/* Returns the current working directory as returned by wgetcwd */
wcstring get_working_directory(void);

#endif
