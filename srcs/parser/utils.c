#include "parser.h"

void	print_redirs(t_redir *r)
{
	while (r)
	{
		printf("   redir: ");
		if (r->type == REDIR_IN) printf("< ");
		else if (r->type == REDIR_OUT) printf("> ");
		else if (r->type == REDIR_APPEND) printf(">> ");
		else if (r->type == REDIR_HEREDOC) printf("<< ");

		if (r->file)
			printf("%s\n", r->file);
		else
			printf("(null)\n");
		r = r->next;
	}
}

void	print_cmd(t_cmd *cmd)
{
	if (!cmd)
	{
		printf("   (CMD NULL)\n");
		return ;
	}

	for (int i = 0; i < cmd->argc; i++)
	{
		if (cmd->argv && cmd->argv[i])
			printf("   argv[%d] = '%s'\n", i, cmd->argv[i]);
		else
			printf("   argv[%d] = (NULL)\n", i);
	}

    print_redirs(cmd->redir);
}

char	*node_type_str(t_node_type type)
{
	if (type == NODE_CMD) return ("CMD");
	if (type == NODE_PIPE) return ("PIPE");
	if (type == NODE_REDIR) return ("REDIR");
	if (type == NODE_AND) return ("AND");
	if (type == NODE_OR) return ("OR");
	if (type == NODE_SEQ) return ("SEQ");
	if (type == NODE_SUB) return ("SUB");
	return ("NUMTEM");
}

void	print_ast(t_ast *node, int depth)
{
	if (!node)
		return ;

	for (int i = 0; i < depth; i++)
		printf("  ");

	printf("[%s]\n", node_type_str(node->type));

	if (node->type == NODE_CMD)
	{
		for (int i = 0; i < depth; i++)
			printf("  ");
		printf("CMD:\n");
		print_cmd((t_cmd *)node->content);
		return ;
	}

	// left
	for (int i = 0; i < depth; i++)
		printf("  ");
	printf(" left →\n");
	print_ast(node->left, depth + 1);

	// right
	for (int i = 0; i < depth; i++)
		printf("  ");
	printf(" right →\n");
	print_ast(node->right, depth + 1);
}

