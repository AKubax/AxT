#include <list>
#include <vector>
#include <algorithm>
#include <iostream>
#include <stdarg.h>
#include <windows.h>
#include <ctype.h>
#include <cstdio>

std::vector<char> evidence;

struct Way{
    std::vector<char> letters;

    Way(int n, char w...)
    {
        char* k = &w;
        for(int i = 0; i < n; i++, k++){
            letters.push_back(*k);
        }
    }

    Way(std::vector<char> l):
    letters (l)
    {}
};

struct Letter{
    std::vector<Way> ways;

    Letter(){}

    void push_way(Way w){
        ways.push_back(w);
    }

    void DEBUG(){
        printf("If you see it, there are no NULLs in letters\n");
    }
};

Letter letters[256];

struct Axiom{
    std::vector<char> causes;
    std::vector<char> result;

    int l_causes = 0;
    int l_results = 0;

    Axiom(int n_causes, int n_results, ...):
    l_causes (n_causes),
    l_results (n_results)
    {
        va_list args;

        va_start(args, n_results);

//        printf("\n\n");
        for(int i = 0; i < n_causes; i++){
//            printf("Before causes.push_back(va_arg(args, char));\n");
            int c = va_arg(args, int);
//            printf("Pushing %c to causes\n", c);
            causes.push_back(c);
//            printf("After\n\n");
//            printf(" '%c'[*p == %c; p == %p]", causes[i], va_arg(args, char), p);
//            p++;
        }
//        printf("\nPrinting result:");
        for(int i = 0; i < n_results; i++){
            int c = va_arg(args, int);
//            printf("Pushing %c to results\n", c);
            result.push_back(c);
//            printf(" '%c'[*p == %c; p == %p]", result[i], *p, p);
//            p++;
        }
        va_end(args);
//        printf("\n\n");
    }
};

void parseAxiom(Axiom ax){
    for(int i = 0; i < ax.l_results; i++){
//        printf("From func parseAxiom. ax.l_results == %d; ax.result[i] == %c\n", ax.l_results, ax.result[i]);
//        printf("Parsing axiom, causes =");
//        for(int i = 0; i < ax.l_causes; i++) printf(" %c", ax.causes[i]);
//        printf("; result =");
//        for(int i = 0; i < ax.l_results; i++) printf(" %c", ax.result[i]);
//        printf("\n\n");

        letters[ax.result[i]].push_way(Way(ax.causes));
    }
}

int theKernel(std::vector<char> check, std::vector<char> available){
    printf("Checking if this chars are available:");  for(int i = 0; i < check.size(); i++) printf(" %c", check[i]); printf("\n");
    int r_value = 0;

    char letter;
    for(int i = 0; i < check.size(); i++){
        letter = check[i];
        if(std::binary_search(available.begin(), available.end(), letter)){
            printf("%c is available(in available)\n", letter);
            r_value = 1;
            continue;
        }
        else{
            printf("%c is not available\n", letter);
            printf("letters[letter [%c]].ways.size() == %d\n", letter, letters[letter].ways.size());
            getchar();              //TODO delete
            for(int i = 0; i < letters[letter].ways.size(); i++){
                if(theKernel(letters[letter].ways[i].letters, available)){
                    printf("%c is available\n", letter);

                    for(int k = 0; k < letters[letter].ways[i].letters.size(); k++){
                        evidence.push_back(letters[letter].ways[i].letters[k]);
                        evidence.push_back(',');
                    }
                    evidence.push_back('>');
                    evidence.push_back(' ');
                    evidence.push_back(letter);
                    evidence.push_back('|');
                    evidence[evidence.size() - 5] = ' ';

                    available.push_back(letter);

                    return 1;
                }
            }
        }
    }
//    printf("Ways to %c are not found\n", letter);

    return r_value;
}

void AxT(std::vector<char> available, std::vector<char> check){
    if(theKernel(check, available)){
        printf("\n\n\nSUCCESSFUL!\n");
        printf("Evidence is: ");
        evidence[evidence.size() - 1] = ' ';
        for(int i = 0; i < evidence.size(); i++) printf("%c ", evidence[i]);
    }
    else{
        printf("Failed :(. No evidence for this theorem");
    }
}

int main(){
    parseAxiom(Axiom(2, 1, 'a','b', 'f'));
    parseAxiom(Axiom(3, 2, 'f','h','j', 'c','d'));
    parseAxiom(Axiom(2, 2, 'a','d', 'b','i'));
    parseAxiom(Axiom(2, 1, 'd','i', 'h'));
    parseAxiom(Axiom(3, 2, 'b','c','g', 'a','j'));
    parseAxiom(Axiom(2, 2, 'e','j', 'f','g'));
    parseAxiom(Axiom(2, 2, 'f','g', 'e','j'));
    parseAxiom(Axiom(3, 2, 'c','d','h', 'a','g'));
    parseAxiom(Axiom(2, 3, 'a','g', 'c','d','h'));
    parseAxiom(Axiom(1, 1, 'a', 'e'));
    parseAxiom(Axiom(1, 1, 'e', 'b'));
    parseAxiom(Axiom(3, 3, 'f','g','h', 'c','d','i'));

//  End of Axioms

    printf("Enter theorem like that: ab>c.\n\n\n");

    std::vector<char> available;
    std::vector<char> check;

    char c;
    while((c = getchar()) != '>'){
        available.push_back(c);
    }
    while((c = getchar()) != '.'){
        check.push_back(c);
    }


    AxT(available, check);
}





