#define TOKKEN_BUFFERSIZE 64
//#define TOK_DELIM " \t\r\n\a"

extern int sigsize;
typedef struct process{
	int  num;
	char pname[50];
    int state;
}process;

struct passwd * myname;
char hostname[30];
char * curname;
process * proc[200];

int foreground_id;

char shellid[10];

void sigz(int signum);
int pinfo_id(char ** args);
int print_details(char *filepath);
void trunc_line(char * str);
int piping(char ** args);

char ** redirect(char ** args);
void sigh(int signum);
    
void print_prompt();
char * itoa(int num , char * pid);
char * pinfostate(int pid);

int overkill(char **args);

char myhome[1024];

char **split_line(char *line,char * delim);

char * read_line();

int change_dir(char **args);

int echo(char ** args);
int jobs(char **args);
int kjob(char **args);
int bg(char **args);
int fg(char **args);
int pwd(char **args);



int launch(char **args);
void list_dir(char **argv);

void detailed_list_dir(char **argv);


int ls(char **argv);

int exit_shell(char ** argv);


int execute(char ** argv);

void signalhandler();

int setVar(char **args);

int unsetVar(char **args);

int main(int argc, char const *argv[]);
