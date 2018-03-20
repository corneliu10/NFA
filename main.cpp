#include <stdio.h>
#include <map>
#include <vector>
#include <set>
#include <cstring>

using namespace std;

class NFA {
    int nr_stari;
    vector<int> stari;

    int nr_lit;
    vector<char> lit;

    int s0,nr_stari_fin;
    vector<int> stari_fin;

    int nr_tranz;
    struct tranzitie {
        int a,b;
        char lit;
        tranzitie(int nr1,int nr2, char lit1) {
            a = nr1;
            b = nr2;
            lit = lit1;
        }
    };
    vector<struct tranzitie> tranz;

    public:
        void read_data(char in_file[])
        {
            FILE *in;
            int i,nr,nr1;
            char ch,word[1000];
            in = fopen(in_file,"r");

            fscanf(in,"%d",&nr_stari);
            for(i=0;i<nr_stari;++i) {
                fscanf(in,"%d",&nr);
                stari.push_back(nr);
            }

            fscanf(in,"%d",&nr_lit);
            for(i=0;i<nr_lit;++i) {
                fscanf(in,"\n%c ",&ch);
                lit.push_back(ch);
            }

            fscanf(in,"%d",&s0);

            fscanf(in,"%d",&nr_stari_fin);
            for(i=0;i<nr_stari_fin;++i) {
                fscanf(in,"%d",&nr);
                stari_fin.push_back(nr);
            }

            fscanf(in,"%d",&nr_tranz);
            for(i=0;i<nr_tranz;++i) {
                fscanf(in,"%d %c %d",&nr,&ch,&nr1);
                tranz.push_back(tranzitie(nr,nr1,ch));
            }

            FILE *out = fopen("data.out","w");

            fscanf(in,"%d",&nr);
            for(i=0;i<nr;i++)
            {
                fscanf(in,"%s",word);
                if(ver_word(word)) fprintf(out,"DA\n");
                else fprintf(out,"NU\n");
            }

            fclose(out);
            fclose(in);
        }

        //returns a list of next_states from state st
        void NFA_move(int st,char lit,set<int> &next_states)
        {
            for(int i=0;i < nr_tranz;i++)
            {
                if(tranz[i].a == st && tranz[i].lit == lit)
                    next_states.insert(tranz[i].b);
            }
        }

        ////returns a list of next_states from states states
        void NFA_move(set<int> states,char lit,set<int> &next_states)
        {
            set<int> tmp;
            for(set<int>::iterator it = states.begin(); it!=states.end(); it++)
                NFA_move(*it,lit,tmp);

            next_states = tmp;
        }

        bool ver_word(char *word) {
            int idx = 0;
            set<int> st,nst;
            st.insert(s0);

            while(idx != strlen(word))
            {
                nst.clear();
                if(st.size() == 1) NFA_move(*(st.begin()), word[idx], nst);
                else if(st.size() > 1) NFA_move(st, word[idx], nst);
                else return false;

                idx++; st = nst;
            }

            for(set<int>::iterator it = st.begin(); it!=st.end(); it++)
                for(int i = 0;i < nr_stari_fin;i++)
                    if(*it == stari_fin[i]) return true;

            return false;
        }
};

/*void read_words(char in_file[]) {
    FILE *in;
    int i,nr;
    char word[100];

    in = fopen(in_file,"r");

    fscanf(in,"%d",&nr);
    for(i=0;i<nr;i++)
    {
        fscanf(in,"%s",word);
        if(nfa.ver_word(word)) printf("DA\n");
        else printf("NU\n");
    }

    fclose(in);
}*/

int main()
{
    NFA nfa;
    nfa.read_data("data.in");
}


