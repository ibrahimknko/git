/*
 * This represents a "patch" to a file, both metainfo changes
 * such as creation/deletion, filemode and content changes represented
 * as a series of fragments.
 */
struct patch {
	char *new_name, *old_name, *def_name;
	unsigned int old_mode, new_mode;
	int is_new, is_delete;	/* -1 = unknown, 0 = false, 1 = true */
	int rejected;
	unsigned ws_rule;
	int lines_added, lines_deleted;
	int score;
	int extension_linenr; /* first line specifying delete/new/rename/copy */
	unsigned int is_toplevel_relative:1;
	unsigned int inaccurate_eof:1;
	unsigned int is_binary:1;
	unsigned int is_copy:1;
	unsigned int is_rename:1;
	unsigned int recount:1;
	unsigned int conflicted_threeway:1;
	unsigned int direct_to_threeway:1;
	unsigned int crlf_in_old:1;
	struct fragment *fragments;
	char *result;
	size_t resultsize;
	char old_oid_prefix[GIT_MAX_HEXSZ + 1];
	char new_oid_prefix[GIT_MAX_HEXSZ + 1];
	struct patch *next;

	/* three-way fallback result */
	struct object_id threeway_stage[3];
};

static char *find_name_gnu(struct apply_state *state,
	 * http://marc.info/?l=git&m=112927316408690&w=2
	if (state->root.len)
		strbuf_insert(&name, 0, state->root.buf, state->root.len);
static char *find_name_common(struct apply_state *state,
	if (state->root.len) {
		char *ret = xstrfmt("%s%.*s", state->root.buf, len, start);
static char *find_name(struct apply_state *state,
		char *name = find_name_gnu(state, line, p_value);
	return find_name_common(state, line, def, p_value, NULL, terminate);
static char *find_name_traditional(struct apply_state *state,
		char *name = find_name_gnu(state, line, p_value);
		return find_name_common(state, line, def, p_value, NULL, TERM_TAB);
	return find_name_common(state, line, def, p_value, line + len, 0);
	name = find_name_traditional(state, nameline, NULL, 0);
		name = find_name_traditional(state, second, NULL, state->p_value);
		name = find_name_traditional(state, first, NULL, state->p_value);
		first_name = find_name_traditional(state, first, NULL, state->p_value);
		name = find_name_traditional(state, second, first_name, state->p_value);
static int gitdiff_hdrend(struct apply_state *state,
static int gitdiff_verify_name(struct apply_state *state,
		*name = find_name(state, line, NULL, state->p_value, TERM_TAB);
		another = find_name(state, line, NULL, state->p_value, TERM_TAB);
static int gitdiff_oldname(struct apply_state *state,
static int gitdiff_newname(struct apply_state *state,
static int gitdiff_oldmode(struct apply_state *state,
static int gitdiff_newmode(struct apply_state *state,
static int gitdiff_delete(struct apply_state *state,
static int gitdiff_newfile(struct apply_state *state,
static int gitdiff_copysrc(struct apply_state *state,
	patch->old_name = find_name(state, line, NULL, state->p_value ? state->p_value - 1 : 0, 0);
static int gitdiff_copydst(struct apply_state *state,
	patch->new_name = find_name(state, line, NULL, state->p_value ? state->p_value - 1 : 0, 0);
static int gitdiff_renamesrc(struct apply_state *state,
	patch->old_name = find_name(state, line, NULL, state->p_value ? state->p_value - 1 : 0, 0);
static int gitdiff_renamedst(struct apply_state *state,
	patch->new_name = find_name(state, line, NULL, state->p_value ? state->p_value - 1 : 0, 0);
static int gitdiff_similarity(struct apply_state *state,
static int gitdiff_dissimilarity(struct apply_state *state,
static int gitdiff_index(struct apply_state *state,
static int gitdiff_unrecognized(struct apply_state *state,
static const char *skip_tree_prefix(struct apply_state *state,
	if (!state->p_value)
	nslash = state->p_value;
static char *git_header_name(struct apply_state *state,
		cp = skip_tree_prefix(state, first.buf, first.len);
			cp = skip_tree_prefix(state, sp.buf, sp.len);
		cp = skip_tree_prefix(state, second, line + llen - second);
	name = skip_tree_prefix(state, line, llen);
			np = skip_tree_prefix(state, sp.buf, sp.len);
			second = skip_tree_prefix(state, name + len + 1,
static int check_header_line(struct apply_state *state, struct patch *patch)
			     patch->extension_linenr, state->linenr);
		patch->extension_linenr = state->linenr;
/* Verify that we recognize the lines following a git header */
static int parse_git_header(struct apply_state *state,
			    const char *line,
			    int len,
			    unsigned int size,
			    struct patch *patch)
	patch->def_name = git_header_name(state, line, len);
	if (patch->def_name && state->root.len) {
		char *s = xstrfmt("%s%s", state->root.buf, patch->def_name);
	state->linenr++;
	for (offset = len ; size > 0 ; offset += len, size -= len, line += len, state->linenr++) {
			int (*fn)(struct apply_state *, const char *, struct patch *);
			res = p->fn(state, line + oplen, patch);
			if (check_header_line(state, patch))
			int git_hdr_len = parse_git_header(state, line, len, size, patch);
			fill_stat_cache_info(ce, &st);