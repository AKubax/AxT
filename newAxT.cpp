#include <list>
#include <vector>
#include <algorithm>
#include <iostream>
#include <stdarg.h>
#include <windows.h>
#include <ctype.h>
#include <cstdio>
#include <string.h>

class Axiom;
class Theorem;

class Axiom{
public:
    std::string from;
    std::string have;

    bool isProved;

    Axiom(std::string f, std::string h):
    from (f),
    have (h),
    isProved (false)
    {}

    Axiom(int n_causes, int n_results, ...)
    {
        va_list args;

        va_start(args, n_results);

        for(int i = 0; i < n_causes; i++){
            int c = va_arg(args, int);
            from.push_back(c);
        }
        for(int i = 0; i < n_results; i++){
            int c = va_arg(args, int);
            have.push_back(c);
        }
        va_end(args);
    }

    bool appropriate(Theorem t);
};
std::vector<Axiom> axi0ms;

class Theorem{
public:
    std::string from;
    std::string have;

    Theorem(std::string f, std::string h):
    from (f),
    have (h)
    {}

    void prove(){
        bool exit = 0;
        while(!exit){
            exit = 1;

            for(Axiom& ax : axi0ms){
//                printf("Trying to prove this ax:"); for(char c : ax.from) printf(" %c", c); printf(" ->"); for(char c : ax.have) printf(" %c", c); printf("\n");
                if((!ax.isProved) && ax.appropriate(*this)){
                    printf("Used axiom: ");
                    for(char c : ax.from) printf("%c ", c);
                    printf("-> ");
                    for(char c : ax.have) printf("%c ", c);
                    printf("\n");

                    for(char c : ax.have) from.push_back(c);

                    for(char f : have){
                        bool found = 0;
                        for(char c : from) if(c == f) found = 1;

                        if(!found) break;
                        else{
                            printf("PROVED!\n\n\n\n\n");
                            return;
                        }
                    }

                    exit = 0;
                }
            }

            if(exit){
                printf("Theorem can't be proved");
            }
        }
    }
};

bool Axiom::appropriate(Theorem t){
    for(char f : from){
        bool found = 0;
        for(char c : t.from) if(c == f) found = 1;
        if(!found) return 0;
    }
    return 1;
}





void parseAxiom(Axiom ax){
    axi0ms.push_back(ax);
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
    parseAxiom(Axiom(1, 1, 'e', 'b'));
    parseAxiom(Axiom(1, 1, 'a', 'e'));
    parseAxiom(Axiom(3, 3, 'f','g','h', 'c','d','i'));

    Theorem("a", "b").prove();
}
