#ifndef __LEX__
#define __LEX__
#define MAXLEN 256
// Token types
typedef enum {
    UNKNOWN,END,ENDFILE,INT,ID,ADDSUB,MULDIV,ASSIGN,LPAREN,RPAREN,
    // new token
    INCDEC,AND,OR,XOR
} TokenSet;
// Test if a token matches the current token
extern int match(TokenSet token);
// Get the next token
extern void advance(void);
// Get the lexeme of the current token
extern char *getLexeme(void);
#endif // __LEX__
#ifndef __PARSER__
#define __PARSER__


#define TBLSIZE 64

// Set PRINTERR to 1 to print error message while calling error()
// Make sure you set PRINTERR to 0 before you submit your code
#define PRINTERR 0

// Call this macro to print error message and exit the program
// This will also print where you called it in your program
#define errors(errorNum) { \
    if (PRINTERR) \
        fprintf(stderr, "error() called at %s:%d: ", __FILE__, __LINE__); \
    errs(errorNum); \
}

// Error types
typedef enum {
    UNDEFINED, MISPAREN, NOTNUMID, NOTFOUND, RUNOUT, NOTLVAL, DIVZERO, SYNTAXERR
} ErrorType;

// Structure of the symbol table
typedef struct {
    int val;
    char name[MAXLEN];
} Symbol;

// Structure of a tree node
typedef struct _Node {
    TokenSet data;
    int val;
    char lexeme[MAXLEN];
    struct _Node *left;
    struct _Node *right;
    //
    int reg;
} BTNode;

// The symbol table
extern Symbol table[TBLSIZE];

// Initialize the symbol table with builtin variables
extern void initTable(void);

// Get the value of a variable
extern int getval(char *str);

// Set the value of a variable
extern int setval(char *str, int val);

extern int ID_pos(char* str);

// Make a new node according to token type and lexeme
extern BTNode *makeNode(TokenSet tok, const char *lexe);

// Free the syntax tree
extern void freeTree(BTNode *root);

extern BTNode *factor(void);
extern BTNode *term(void);
extern BTNode *term_tail(BTNode *left);
extern BTNode *expr(void);
extern BTNode *expr_tail(BTNode *left);
extern void statement(void);
//=====================================
extern BTNode * assign_expr(void);
extern BTNode * or_expr(void);
extern BTNode * or_expr_tail(BTNode *left);
extern BTNode * xor_expr(void);
extern BTNode * xor_expr_tail(BTNode *left);
extern BTNode * and_expr(void);
extern BTNode * and_expr_tail(BTNode *left);
extern BTNode * addsub_expr(void);
extern BTNode * addsub_expr_tail(BTNode *left);
extern BTNode * muldiv_expr(void);
extern BTNode * muldiv_expr_tail(BTNode *left);
extern BTNode * unary_expr(void);

// Print error message and exit the program
extern void errs(ErrorType errorNum);

#endif // __PARSER__

#ifndef __CODEGEN__
#define __CODEGEN__

// Evaluate the syntax tree
extern void evaluateTree(BTNode *root);
// Print the syntax tree in prefix
extern void printPrefix(BTNode *root);
#endif // __CODEGEN__
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

static TokenSet getToken(void);
static TokenSet curToken = UNKNOWN;
static char lexeme[MAXLEN];

TokenSet getToken(void)
{
    int i = 0;
    char c = '\0';

    while ((c = fgetc(stdin)) == ' ' || c == '\t');

    if (isdigit(c)) {
        lexeme[0] = c;
        c = fgetc(stdin);
        i = 1;
        while (isdigit(c) && i < MAXLEN) {
            lexeme[i] = c;
            ++i;
            c = fgetc(stdin);
        }
        ungetc(c, stdin);
        lexeme[i] = '\0';
        return INT;
    }
    else if (c == '+' || c == '-') {
        //=================
        char z = fgetc(stdin);
        if((c=='+'&&z=='+')||(c=='-'&&z=='-')){
            lexeme[0] = c;
            lexeme[1] = z;
            lexeme[2] = '\0';
            //printf("find ++ or --\n");
            return INCDEC;
        }
        else ungetc(z, stdin);
        //==================
        lexeme[0] = c;
        lexeme[1] = '\0';
        return ADDSUB;
    }
    else if (c == '*' || c == '/') {
        lexeme[0] = c;
        lexeme[1] = '\0';
        return MULDIV;
    }
    else if (c == '\n') {
        lexeme[0] = '\0';
        return END;
    }
    else if (c == '=') {
        strcpy(lexeme, "=");
        return ASSIGN;
    }
    else if (c == '(') {
        strcpy(lexeme, "(");
        return LPAREN;
    }
    else if (c == ')') {
        strcpy(lexeme, ")");
        return RPAREN;
    }
    else if (isalpha(c)||c=='_') {
        //==========================
        lexeme[0] = c;
        c = fgetc(stdin);
        i = 1;
        while (c!='='&&c!='+'&&c!='-'&&c!='*'&&c!='/'&&c!='|'&&c!='&'&&c!='^'&&c!='\n'&&c!='('&&c!=')'&&c!=' '&&c!='\t') {
            lexeme[i] = c;
            ++i;
            c = fgetc(stdin);
        }
        ungetc(c, stdin);
        lexeme[i] = '\0';
        return ID;
    }
    //=========================
    else if(c== '&'){
        lexeme[0] = c;
        lexeme[1] = '\0';
        return AND;
    }
    else if(c=='|'){
        lexeme[0] = c;
        lexeme[1] = '\0';
        return OR;
    }
    else if(c=='^'){
        lexeme[0] = c;
        lexeme[1] = '\0';
        return XOR;
    }
    //=========================
    else if (c == EOF) {
        return ENDFILE;
    }
    else {
        return UNKNOWN;
    }
}

void advance(void) {
    curToken = getToken();
}

int match(TokenSet token) {
    if (curToken == UNKNOWN)
        advance();
    return token == curToken;
}

char *getLexeme(void) {
    return lexeme;
}



int sbcount = 0;
Symbol table[TBLSIZE];
BTNode* tempID = NULL;

void initTable(void) {
    strcpy(table[0].name, "x");
    table[0].val = 0;
    strcpy(table[1].name, "y");
    table[1].val = 0;
    strcpy(table[2].name, "z");
    table[2].val = 0;
    sbcount = 3;
}

int ID_pos(char* str){
    for(int i=0;i<sbcount;i++){
        if (strcmp(str, table[i].name) == 0){
            return i*4;
        }
    }
    return -1;
}

int getval(char *str) {
    int i = 0;
    for (i = 0; i < sbcount; i++)
        if (strcmp(str, table[i].name) == 0)
            return table[i].val;

    if (sbcount >= TBLSIZE){
        printf("EXIT 1\n");
        errors(RUNOUT);
        exit(0);
    }
    
    strcpy(table[sbcount].name, str);
    table[sbcount].val = 0;
    sbcount++;
    return 0;
}

int setval(char *str, int val) {
    int i = 0;

    for (i = 0; i < sbcount; i++) {
        if (strcmp(str, table[i].name) == 0) {
            table[i].val = val;
            return val;
        }
    }

    if (sbcount >= TBLSIZE){
        printf("EXIT 1\n");
        errors(RUNOUT);
        exit(0);
    }
        
    strcpy(table[sbcount].name, str);
    table[sbcount].val = val;
    sbcount++;
    return val;
}

BTNode *makeNode(TokenSet tok, const char *lexe) {
    BTNode *node = (BTNode*)malloc(sizeof(BTNode));
    strcpy(node->lexeme, lexe);
    node->data = tok;
    node->val = 0;
    node->left = NULL;
    node->right = NULL;
    node->reg = 0;
    return node;
}

void freeTree(BTNode *root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}
//=================================================

// statement := ENDFILE | END | expr END
//:= END | assign_expr END
void statement(void) {
    BTNode *retp = NULL;

    if (match(ENDFILE)) {
        printf("MOV r0 [0]\nMOV r1 [4]\nMOV r2 [8]\n");
        printf("EXIT 0\n");
        exit(0);
    }
    else if (match(END)) {
        advance();
    }
    else {
        retp = assign_expr();
        if (match(END)) {
            evaluateTree(retp);
            //printf("x=%d",getval("x"));
            printPrefix(retp); //reset all register
            freeTree(retp);
            advance();
        }
        else {
            printf("EXIT 1\n");
            errors(SYNTAXERR);
            exit(0);
        }
    }
}
//assign_expr:= ID ASSIGN assign_expr | or_expr
BTNode * assign_expr(void){
    BTNode* node = NULL;
    
    if(match(ID)){
        
        tempID = makeNode(ID, getLexeme());
        advance();
        if(match(ASSIGN)){
            node = makeNode(ASSIGN, getLexeme());
            advance();
            node->left = tempID;
            tempID = NULL;
            node->right = assign_expr();
        }
        else{
            //=================
            // 14 runtime error -> wrong anwser
            int check = ID_pos(tempID->lexeme);
            //printf("%s",tempID->lexeme);
            if(check==-1){
                printf("EXIT 1\n");
                exit(0);
            }
            
            //==================
            node = or_expr();
        }
    }
    else{
        node = or_expr();
    }
        
        
    return node;
    
    //return NULL;
}
//or_expr:= xor_expr or_expr_tail
BTNode * or_expr(void){
    BTNode* node = xor_expr();
    return or_expr_tail(node);
}
//or_expr_tail:= OR xor_expr or_expr_tail | NiL
BTNode * or_expr_tail(BTNode *left){
    BTNode* node = NULL;
    if(match(OR)){
        node = makeNode(OR, getLexeme());
        advance();
        node->left = left;
        node->right = xor_expr();
        return or_expr_tail(node);
    }
    else{
        return left;
    }
}
//xor_expr:= and_expr xor_expr_tail
BTNode * xor_expr(void){
    BTNode* node = and_expr();
    return xor_expr_tail(node);
}
//xor_expr_tail:= XOR and_expr xor_expr_tail | NiL
BTNode * xor_expr_tail(BTNode *left){
    BTNode* node = NULL;
    if(match(XOR)){
        node = makeNode(XOR, getLexeme());
        advance();
        node->left = left;
        node->right = and_expr();
        return xor_expr_tail(node);
    }
    else{
        return left;
    }
}
//and_expr:= addsub_expr and_expr_tail
BTNode * and_expr(void){
    BTNode* node =addsub_expr();
    return and_expr_tail(node);
}
//and_expr_tail:= AND addsub_expr and_expr_tail | NiL
BTNode * and_expr_tail(BTNode *left){
    BTNode* node = NULL;
    if(match(AND)){
        node = makeNode(AND, getLexeme());
        advance();
        node->left = left;
        node->right = addsub_expr();
        return and_expr_tail(node);
    }
    else{
        return left;
    }
}
//addsub_expr:= muldiv_expr addsub_expr_tail
BTNode * addsub_expr(void){
    BTNode* node = muldiv_expr();
    return addsub_expr_tail(node);
}
//addsub_expr_tail:= ADDSUB muldiv_expr addsub_expr_tail | NiL
BTNode * addsub_expr_tail(BTNode *left){
    BTNode* node = NULL;
    if(match(ADDSUB)){
        node = makeNode(ADDSUB, getLexeme());
        advance();
        node->left = left;
        node->right = muldiv_expr();
        return addsub_expr_tail(node);
    }
    else{
        return left;
    }
}
//muldiv_expr:= unary_expr muldiv_expr_tail
BTNode * muldiv_expr(void){
    BTNode* node =  unary_expr();
    return muldiv_expr_tail(node);
}
//muldiv_expr_tail:= MULDIV unary_expr muldiv_expr_tail | NiL
BTNode * muldiv_expr_tail(BTNode *left){
    BTNode* node = NULL;
    if(match(MULDIV)){
        node = makeNode(MULDIV, getLexeme());
        advance();
        node->left = left;
        node->right = unary_expr();
        return muldiv_expr_tail(node);
    }
    else{
        return left;
    }
}
//unary_expr:= ADDSUB unary_expr | factor
BTNode * unary_expr(void){
    BTNode* node = NULL;
    if(tempID!=NULL){
        node = tempID;
        tempID = NULL;
    }
    else if(match(ADDSUB)){
        char x[10]={};
        strcpy(x, getLexeme());
        
        node = makeNode(MULDIV, "*");
        advance();
        if(x[0]=='+')
            node->left = makeNode(INT, "1");
        else if(x[0]=='-')
            node->left = makeNode(INT, "-1");
        
        node->right = unary_expr();
    }
    else{
       node = factor();
    }
    return node;
}
//INT | ID | INCDEC ID | LPAREN assign_expr RPAREN
BTNode *factor(void) {
    BTNode *retp = NULL;
    
    if (match(INT)) {
        retp = makeNode(INT, getLexeme());
        advance();
    }
    else if (match(ID)) {
        retp = makeNode(ID, getLexeme());
        //=================
        int check = ID_pos(retp->lexeme);
        if(check==-1){
            printf("EXIT 1\n");
            exit(0);
        }
        //==================
        advance();
    }
    else if (match(INCDEC)) {
        retp = makeNode(INCDEC, getLexeme());
        advance();
        if(match(ID)){
            retp->left = makeNode(ID, getLexeme());
            //
            int check = ID_pos(getLexeme());
            if(check==-1){
                printf("EXIT 1\n");
                exit(0);
            }
            //
            advance();
            retp->right = makeNode(INT, "1");
        }
        else{
            printf("EXIT 1\n");
            errors(SYNTAXERR);
            exit(0);
        }
    }
    else if (match(LPAREN)) {
        advance();
        retp = assign_expr();
        if (match(RPAREN)){
            advance();
        }
        else{
            printf("EXIT 1\n");
            errors(MISPAREN);
            exit(0);
        }
    }
    else {
        printf("EXIT 1\n");
        errors(NOTNUMID);
        exit(0);
    }
    return retp;
}

//=====================================================================
void errs(ErrorType errorNum) {
    if (PRINTERR) {
        fprintf(stderr, "error: ");
        switch (errorNum) {
            case MISPAREN:
                fprintf(stderr, "mismatched parenthesis\n");
                break;
            case NOTNUMID:
                fprintf(stderr, "number or identifier expected\n");
                break;
            case NOTFOUND:
                fprintf(stderr, "variable not defined\n");
                break;
            case RUNOUT:
                fprintf(stderr, "out of memory\n");
                break;
            case NOTLVAL:
                fprintf(stderr, "lvalue required as an operand\n");
                break;
            case DIVZERO:
                fprintf(stderr, "divide by constant zero\n");
                break;
            case SYNTAXERR:
                fprintf(stderr, "syntax error\n");
                break;
            default:
                fprintf(stderr, "undefined error\n");
                break;
        }
    }
    exit(0);
}

typedef struct r{
    int used;
    int val;
}R;
R reg[8] = {{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}};
int getreg(){
    for(int i=0;i<8;i++){
        if(reg[i].used==0){
            reg[i].used = 1;
            return i;
        }
    }
    return -1;
}


void asscode(BTNode *root,char* oder){

    if(root->left->data==ID){
        int x = getreg();
        root->left->reg = x;
        reg[x].val = root->left->val;
        int pos = ID_pos(root->left->lexeme);
        printf("MOV r%d [%d]\n",root->left->reg,pos);
    }
    else if(root->left->data==INT){
        int x = getreg();
        root->left->reg = x;
        reg[x].val = root->left->val;
        int num = root->left->val;
        printf("MOV r%d %d\n",root->left->reg,num);
    }
    else if(root->left==NULL){
        printf("EXIT 1\n");
        exit(0);
    }
    //==================================================
    
    if(root->right->data==ID){
        int x = getreg();
        root->right->reg = x;
        reg[x].val = root->right->val;
        int pos = ID_pos(root->right->lexeme);
        printf("MOV r%d [%d]\n",root->right->reg,pos);
    }
    else if(root->right->data==INT){
        int x = getreg();
        root->right->reg = x;
        reg[x].val = root->right->val;
        int num = root->right->val;
        printf("MOV r%d %d\n",root->right->reg,num);
    }
    else if(root->right==NULL){
        printf("EXIT 1\n");
        exit(0);
    }
    //===================================================
    printf("%s r%d r%d\n",oder,root->left->reg,root->right->reg);
}

void evaluateTree(BTNode *root){
    
    if(root==NULL) return;
    //左
    evaluateTree(root->left);
    //右
    evaluateTree(root->right);
    //中
    if(root!=NULL){
        if(root->data==INT){
            root->val = atoi(root->lexeme);
        }
        else if(root->data==ID){
            root->val = getval(root->lexeme);
        }
        else if(root->data==ADDSUB){
            if(root->lexeme[0]=='+'){
                asscode(root, "ADD");
                reg[root->left->reg].val += reg[root->right->reg].val;
                root->reg = root->left->reg;
                reg[root->right->reg].used = 0;
            }
            else if(root->lexeme[0]=='-'){
                asscode(root, "SUB");
                reg[root->left->reg].val -= reg[root->right->reg].val;
                root->reg = root->left->reg;
                reg[root->right->reg].used = 0;
            }
        }
        else if(root->data==INCDEC){
            if(root->lexeme[0]=='+'){
                asscode(root, "ADD");
                reg[root->left->reg].val += reg[root->right->reg].val;
                root->reg = root->left->reg;
                reg[root->right->reg].used = 0;
                //
                setval(root->left->lexeme, reg[root->reg].val);
                int pos = ID_pos(root->left->lexeme);
                printf("MOV [%d] r%d\n",pos,root->reg);
                
            }
            else if(root->lexeme[0]=='-'){
                asscode(root, "SUB");
                reg[root->left->reg].val -= reg[root->right->reg].val;
                root->reg = root->left->reg;
                reg[root->right->reg].used = 0;
                //
                setval(root->left->lexeme, reg[root->reg].val);
                int pos = ID_pos(root->left->lexeme);
                printf("MOV [%d] r%d\n",pos,root->reg);
            }
        }
        else if(root->data==MULDIV){
            if(root->lexeme[0]=='*'){
                asscode(root, "MUL");
                reg[root->left->reg].val *= reg[root->right->reg].val;
                root->reg = root->left->reg;
                reg[root->right->reg].used = 0;
            }
            else if(root->lexeme[0]=='/'){
                //
                asscode(root, "DIV");
                if(root->right->data!=ID&&reg[root->right->reg].val==0){
                    printf("EXIT 1\n");
                    exit(0);
                }
                
                reg[root->left->reg].val /= reg[root->right->reg].val;
                root->reg = root->left->reg;
                reg[root->right->reg].used = 0;
            }
        }
        else if(root->data==OR){
            asscode(root, "OR");
            int anw = reg[root->left->reg].val | reg[root->right->reg].val;
            reg[root->left->reg].val = anw;
            root->reg = root->left->reg;
            reg[root->right->reg].used = 0;
        }
        else if(root->data==XOR){
            asscode(root, "XOR");
            int anw = reg[root->left->reg].val ^ reg[root->right->reg].val;
            reg[root->left->reg].val = anw;
            root->reg = root->left->reg;
            reg[root->right->reg].used = 0;
        }
        else if(root->data==AND){
            asscode(root, "AND");
            int anw = reg[root->left->reg].val & reg[root->right->reg].val;
            reg[root->left->reg].val = anw;
            root->reg = root->left->reg;
            reg[root->right->reg].used = 0;
        }
        else if(root->data==ASSIGN){
            asscode(root, "MOV");
            
            reg[root->left->reg].val = reg[root->right->reg].val;
            root->reg = root->left->reg;
            reg[root->right->reg].used = 0;
            //
            setval(root->left->lexeme, reg[root->reg].val);
            int pos = ID_pos(root->left->lexeme);
            printf("MOV [%d] r%d\n",pos,root->reg);
            
        }
    }
}

void printPrefix(BTNode *root) {
    for(int i=0;i<8;i++){
        reg[i].used = 0;
    }
}

int main() {
    initTable();
    while (1) {
        statement();
    }
    return 0;
}

