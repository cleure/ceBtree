#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "btree.h"

char *table[] = {
    "mysqladmin", "sudoedit", "rssh", "enc2xs", "hg", "less", "git-describe", "tzselect", "apu-1-config", "mysqloptimize", "rcsclean", "mysql_tableinfo", "svnshell", "fc-cat", "pgrep", "tload", "logger", "rename.ul", "git-bisect", "identify", "merge", "ucs2any", "w", "git-fmt-merge-msg", "slon_start", "gitmkdirs", "apropos", "vim.basic", "ps2pdf12", "expiry", "mandb", "pg_lsclusters", "splitfont", "git-merge-resolve", "[", "pdb", "batch", "automake", "ssh-copy-id", "php-config5", "callgrind_control", "aclocal-1.10", "defoma-app", "lft", "git-stash", "slonik_drop_set", "bashbug", "dh_bash-completion", "autom4te", "git-lost-found", "sha512sum", "nmap", "slony_logshipper", "unexpand", "pfbtopfa", "chattr", "mako-render", "rst2man.py", "mysql_upgrade", "rstpep2html.py", "edit", "x86_64-linux-gnu-gcc-4.3", "libtool", "c89", "ndb_show_tables", "valgrind-listener", "gpg-zip", "git-rev-parse", "git-fast-export", "open", "sha1sum", "pstree", "pg_config", "git-merge-base", "rpcinfo", "g++", "pear", "sudo", "lsattr", "git-merge-ours", "head", "piconv", "fc-list", "fold", "omshell", "corelist", "rmiregistry", "pygmentize", "nohup", "convert", "grmid-4.3", "slonik_drop_node", "soelim", "partx", "mysqld_multi", "dbmmanage", "rcp", "pmap", "slonik", "ctstat", "captoinfo", "pydoc", "git-verify-tag", "catchsegv", "GET", "mysql_explain_log", "gsnd", "bsd-write", "msql2mysql", "gitaction", "gkeytool-4.3", "unix2dos", "crontab", "tracd", "autocvs", "tput", "gcov", "gtk-update-icon-cache", "ex", "i386", "HEAD", "git-show", "screen", "gitps", "compile_et", "git-unpack-objects", "git-read-tree", "git-diff", "java", "git-whatchanged", "createuser", "troff", "fmt", "slon", "ps2ascii", "pod2usage", "trac-admin", "gitfm", "rst2latex.py", "font2c", "git-ls-remote", "awk", "mysqltest_embedded", "unzipsfx", "slogin", "git-clean", "setlogcons", "mogrify", "whereis", "innochecksum", "x86_64-linux-gnu-cpp", "dotlockfile", "dvipdf", "chage", "ps2ps2", "display", "valgrind.bin", "chkdupexe", "vimdiff", "X11", "zipgrep", "mysqltestmanager-pwgen", "mysqld_safe", "xzgrep", "mysql_secure_installation", "tcptraceroute", "git-checkout-index", "git-log", "git-mailinfo", "py_compilefiles", "csslint-0.6", "dh_pysupport", "ntpq", "autoconf", "red", "chvt", "perl5.10.0", "libtasn1-config", "composite", "make", "man", "diff3", "git-unpack-file", "git-hash-object", "gdb", "whoami", "x86_64-linux-gnu-g++", "lzmainfo", "dropdb", "gpgv", "charset", "htdigest", "nroff", "pinky", "mailq", "gcov-4.3", "pic", "ssh-add", "apu-config", "debconf-set-selections", "cython", "git-verify-pack", "tic", "resolve_stack_dump", "git-branch", "split", "ps2epsi", "pdfopt", "dh_installdefoma", "c99-gcc", "git-repo-config", "automake-1.4", "ldd", "gitregrep", "gpic", "apt-sortpkgs", "traceroute", "shuf", "mysqltest", "flock", "rst2odt_prepstyles.py", "mysql_client_test", "git-show-ref", "comm", "svnsync", "slonik_move_set", "libgnutls-extra-config", "unicode_stop", "ndb_drop_index", "cpack", "debconf-apt-progress", "mcookie", "pkill", "pg_dumpall", "splain", "git-name-rev", "gcc", "krb5-config", "mysqldump", "git-write-tree", "pysupport-parseversions", "x86_64", "udevinfo", "bfg2pyramid", "git-shortlog", "gslj", "x86_64-linux-gnu-g++-4.3", "gitview", "netkit-ftp", "mbchk", "cpp", "rst2pseudoxml.py", "scp", "replace", "savelog", "git-http-push", "git-checkout", "shasum", "du", "hostid", "sha384sum", "bdftopcf", "view", "tasksel", "sha224sum", "wall", "ps2txt", "pdf2ps", "autoreconf", "pyversions", "git-diff-tree", "mcview", "mysqldumpslow", "git-upload-archive", "slonik_unsubscribe_set", "slabtop", "grog", "c99", "pftp", "slonik_print_preamble", "git-fsck", "lwp-rget", "defoma-user", "fc-cache", "git-annotate", "mkfontscale", "git-cherry-pick", "git-pack-objects", "dumpsexp", "tail", "nl", "report-hw", "apt-extracttemplates", "gij-4.3", "sum", "slon_kill", "printenv", "psed", "slonik_update_nodes", "apr-config", "c++", "mysql_setpermission", "pdb2.5", "sort", "lesspipe", "git-http-fetch", "cpanp-run-perl", "defoma-hints", "mysqlanalyze", "pg_restore", "mysqltestmanager", "perlivp", "git-ls-files", "prename", "git-config", "createlang", "pod2text", "infobrowser", "ps2pdf13", "automake-1.10", "groups", "git-update-ref", "rlog", "tracert", "mx", "ndb_select_all", "rst2newlatex.py", "dig", "unit2-2.5", "debconf-escape", "pstruct", "ntpsweep", "getkeycodes", "gdk-pixbuf-query-loaders", "git-merge-tree", "svnversion", "svn", "cksum", "col", "ftp", "git-peek-remote", "aclocal", "lwp-mirror", "aptitude-create-state-bundle", "git-cvsimport", "c++filt", "resolveip", "git-fsck-objects", "libnetcfg", "unzip", "lspgpot", "ssh-argv0", "git-relink", "tclsh8.5", "valgrind", "pgsql2shp", "php-config", "git-bundle", "gpasswd", "dropuser", "unit2", "yes", "git-pull", "memcached", "git-prune-packed", "pilfont.py", "git-reflog", "top", "rcsfreeze", "ndb_delete_all", "prove", "txt", "git-mktag", "rcs2log", "line", "git-clone", "git-fetch-pack", "git-pack-redundant", "tr", "git-check-ref-format", "screendump", "rsh", "mysql_convert_table_format", "update-pciids", "ifnames", "mysql_config", "openssl-vulnkey", "instmodsh", "psfaddtable", "gcc-4.3", "printf", "mcmfmt", "sensible-browser", "git-merge-recursive", "mcview-debian", "rvim", "rename", "my_print_defaults", "bdftruncate", "easy_install-2.4", "git-show-branch", "myisam_ftdump", "rcsmerge", "slonik_failover", "droplang", "myisamlog", "gprof", "python", "ssh", "env", "gencat", "atq", "git-commit-tree", "mawk", "git-patch-id", "ucfq", "apt-config", "pwdx", "git-rev-list", "rst2xml.py", "cvsps", "pecl", "eqn", "getopt", "git-apply", "ptx", "linux64", "cg_annotate", "addr2line", "git-parse-remote", "stat", "linux32", "ps2pdfwr", "git-mktree", "sdiff", "slonik_init_cluster", "ndb_test_platform", "cal", "defoma-id", "lastb", "vim", "mysqltestmanagerc", "git-rebase", "lwp-download", "ionice", "deallocvt", "pod2latex", "mkpasswd", "sqlite", "whois", "killall", "mcedit-debian", "mysql_install_db", "runcon", "c2ph", "oldfind", "setkeycodes", "ssh-keygen", "rsync", "traceproto.db", "perl", "vi", "gslp", "git-rerere", "mysql_client_test_embedded", "install", "ld", "mysqlcheck", "w.procps", "ndb_mgm", "git-gc", "routel", "ul", "gpg-convert-from-106", "tsort", "write", "infokey", "c_rehash", "xzless", "mkfontdir", "s3cmd", "tclsh", "dirname", "pico", "apr-1-config", "basename", "rst2html.py", "grotty", "pr", "font2psf", "odbcinst", "dumpkeys", "innotop", "git-init", "lzma", "h2xs", "git-var", "git-grep", "x86_64-linux-gnu-cpp-4.3", "git-index-pack", "psfgettable", "traceroute-nanog", "rst2odt.py", "g++-4.3", "git-rebase--interactive", "cc", "php-cgi", "gpg", "kbd_mode", "git-cherry", "find", "ndb_size", "bmon", "codepage", "nawk", "sprof", "pilprint.py", "nad2bin", "dh_pycentral", "addpart", "sg", "shtool", "dos2unix", "passwd", "setsid", "vim.tiny", "ncursesw5-config", "script", "ps2pdf", "tabs", "git-sh-setup", "xzcat", "m4", "libgcrypt-config", "namei", "git-merge", "slonik_create_set", "libgnutls-config", "lessecho", "getent", "size", "as", "psql", "git-upload-pack", "cpan", "ntpdc", "git-diff-files", "funzip", "dpkg-query", "slony_show_configuration", "rebuild-gcj-db", "nm", "pildriver.py", "dbiprof", "git-imap-send", "mysqlimport", "git-prune", "defoma", "ucf", "gitwhich", "git-pack-refs", "ms_print", "tcptraceroute.db", "rlogin", "calendar", "myisampack", "mysql_fix_privilege_tables", "perlbug", "lft.db", "git-stripspace", "sensible-editor", "gitkeys", "tee", "nano", "patch", "rcsdiff", "scriptreplay", "sphinx-quickstart", "git-fetch", "svndumpfilter", "tty", "gvimtutor", "phpize", "lspci", "bdftops", "look", "ptardiff", "conjure", "reindexdb", "git-repack", "ident", "dpkg-trigger", "svn-populate-node-origins-index", "bsd-mailx", "lsusb", "mysql_zap", "eps2eps", "geqn", "gpgsplit", "xz", "Mail", "django-admin.py", "pdf2dsc", "aptitude", "git-daemon", "rev", "git-count-objects", "ipcrm", "md5sum", "sphinx-build", "pathchk", "colcrt", "objcopy", "mailx", "fastjar", "iptables-xml", "colrm", "dbilogstrip", "htdbm", "chfn", "php", "mysqlbug", "POST", "unxz", "strings", "callgrind_annotate", "vimtutor", "traceroute6.db", "proj", "wget", "git-am", "ndb_drop_table", "git-symbolic-ref", "pg_ctlcluster", "pg_dump", "nsupdate", "compose", "mysql_upgrade_shell", "gitmount", "traceroute.db", "easy_install-2.5", "import", "chsh", "free", "slonik_uninstall_nodes", "unicode_start", "git-rm", "zone", "git-cat-file", "createdb", "mkfifo", "git-merge-subtree", "git-reset", "whiptail", "mysql_fix_extensions", "locale", "git-revert", "fix_bs_and_del", "showcfont", "php5", "s2p", "xxd", "libtoolize", "pod2man", "git-check-attr", "vacuumlo", "objdump", "peekfd", "git-receive-pack", "expand", "manpath", "tracert.db", "ncurses5-config", "id", "jar", "fc-match", "rmid", "lcf", "orbd", "cvs", "gorbd-4.3", "sphinx-autogen", "pf2afm", "serialver", "cmake", "info", "rview", "gcore", "factor", "slonik_subscribe_set", "grops", "ssh-keyscan", "see", "pcimodules", "clusterdb", "grepjar", "ddate", "aclocal-1.4", "git-for-each-ref", "base64", "git-merge-stupid", "git-merge-index", "aptitude-run-state-bundle", "users", "ndb_waiter", "gitunpack", "dprofpp", "link", "curl-config", "git-mergetool", "grmiregistry-4.3", "mysql_tzinfo_to_sql", "localedef", "pydoc2.5", "git-shell", "dpkg-split", "git-ls-tree", "montage", "newaliases", "pcre-config", "nstat", "tac", "catman", "file", "md5sum.textutils", "peardev", "vacuumdb", "git-quiltimport", "mtrace", "openvt", "apt-key", "todos", "sftp", "xsubpp", "git-archive", "no_op_client_for_valgrind", "a2p", "mysqlhotcopy", "pg_createcluster", "keytool", "pysupport-movemodules", "host", "lexgrog", "git-status", "xzegrep", "taskset", "dumphint", "git-fast-import", "gserialver-4.3", "from", "lzcat", "slonik_execute_script", "touch", "faillog", "git-cvsserver", "lesskey", "dircolors", "fromdos", "unit2.py", "git-remote", "x86_64-linux-gnu-gcc", "ipcs", "ncal", "ndb_config", "debconf", "git-blame", "paperconf", "traceroute-nanog.db", "git-merge-octopus", "shred", "pg_upgradecluster", "acpi", "oldfuser", "slon_watchdog", "reset", "ntptrace", "mkbimage", "lorder", "git-add--interactive", "gitrgrep", "telnet", "newgrp", "find2perl", "seq", "setarch", "autoheader", "git-diff-index", "pkg-config", "whatis", "mail", "paste", "git-web--browse", "last", "openssl", "gitwipe", "lessfile", "mysqlreport", "soa", "pager", "psfstriptable", "geod", "defoma-psfont-installer", "printafm", "at", "dpkg-deb", "chcon", "myisamchk", "print", "setpci", "pg_dropcluster", "autoupdate", "nice", "git-update-index", "helpztags", "curl", "ndb_select_count", "podchecker", "clear", "run-mailcap", "gs", "setleds", "git-init-db", "ucfr", "acpi_listen", "apt-cache", "ssh-vulnkey", "gsbj", "strip", "autocvsd", "git-cvsexportcommit", "git-update-server-info", "chrt", "gsdj500", "git-send-pack", "cpan2dist", "mysqlshow", "ranlib", "python2.5-config", "gpg-error-config", "setterm", "comp_err", "c89-gcc", "xzmore", "setmetamode", "svnmucc", "git-tag", "pl2pm", "gitdpkgname", "slonik_merge_sets", "pilfile.py", "ccmake", "sensible-pager", "animate", "git-commit", "traceproto", "unlzma", "ps2ps", "pg", "zdump", "routef", "zipinfo", "defoma-subst", "debconf-copydb", "nslookup", "ci", "shp2pgsql", "uptime", "diff", "mysqlaccess", "git-mv", "debconf-communicate", "ssh-agent", "rgrep", "mesg", "gtk-query-immodules-2.0", "unlink", "podselect", "php5-cgi", "python2.5", "gitxgrep", "clear_console", "delpart", "csplit", "hexdump", "cg_merge", "gitrfgrep", "pod2html", "git-format-patch", "invproj", "logname", "gdbtui", "tbl", "vmstat", "apt-ftparchive", "debconf-show", "slonik_store_node", "ndb_error_reporter", "ndb_restore", "pycentral", "git-get-tar-commit-id", "od", "rpcgen", "cut", "atrm", "perldoc", "git-mailsplit", "shtoolize", "git", "infotocap", "join", "apt-get", "traceroute6", "snice", "ndb_desc", "co", "wc", "gpg-error", "test", "mysql_find_rows", "ptar", "slonik_drop_table", "slon_watchdog2", "git-filter-branch", "xargs", "readelf", "xzcmp", "gdbserver", "xzdiff", "perror", "kbd-config", "git-instaweb", "svnserve", "git-submodule", "zsoelim", "infocmp", "git-fetch--tool", "neqn", "mysql_waitpid", "lnstat", "wftopfa", "gitsquidd", "git-merge-one-file", "groff", "pygettext2.5", "xzfgrep", "who", "easy_install", "tset", "column", "lastlog", "rcs", "ghostscript", "ns", "iconv", "dbiproxy", "paster", "ps2pdf14", "dh_installxmlcatalogs", "mcedit", "ctest", "editor", "cpp-4.3", "htpasswd", "gcj-dbtool-4.3", "gtbl", "apt-cdrom", "mysql", "telnet.netkit", "yui-compressor", "rtstat", "cpanp", "dpkg", "gsdj", "mk_modmap", "fonttosfnt", "showkey", "pilconvert.py", "rst2s5.py", "autoscan", "fdformat", "which", "apt-mark", "mysqlrepair", "svnadmin", "stream", "mc", "watch", "cmp", "pcretest", "phpize5", "git-add", "cs2cs", "defoma-font", "uniq", "expr", "git-show-index", "compare", "ar", "git-request-pull", "hd", "toe", "slonik_restart_node", "getconf", "invgeod", "mysqlbinlog", "sha256sum", "skill", "git-merge-file", "pstree.x11", "svnlook", "pygettext", "renice", "aaaa", "config_data", "git-tar-tree", "h2ph", "consolechars", "slonik_build_env", "git-push", "nad2nad", "lwp-request", "vt-is-UTF8", 
};

/**
* Used defined free function, called when a node is free'd.
*
* @param    ceBtreeNode *node
* @return   void
**/
void my_free_function(ceBtreeNode *node)
{
    free(node->data);
    node->key = NULL;
    node->data = NULL;
}

int main(int argc, char **argv)
{
    int i = 0,
        l = (sizeof(table) / sizeof(table[0]));
    ceBtree *tree;
    ceBtreeNode **array;
    
    tree = ceBtree_Init(
        ceBtreeStrcmp,
        my_free_function);

    while (i < l) {
        char *tmp = malloc((sizeof(char) * strlen(table[i])) + 1);
        strcpy(tmp, table[i]);
        
        tree->insert(tree, tmp, tmp, 0);
        ++i;
    }
    
    array = ceBtreeToArray(tree, NULL, &l);
    for (i = 0; i < l; ++i) {
        printf("%s\n", (char *)array[i]->key);
    }

    ceBtreeToArray_Free(&array);
    ceBtree_Free(&tree);

    return 0;
}
