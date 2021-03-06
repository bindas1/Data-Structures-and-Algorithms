#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <chrono>

using Index = std::vector<int>;

char randomChar(){
  return 'a' + rand()%3;
}

std::string randomize(int len){
  std::string str = "";
  for(auto i = 0; i < len; i++){
    str += randomChar();
  }
  return str;
}

std::vector<int> BruteFind(std::string const & text, std::string const & str){
  std::vector<int> indices;

  int key_length = text.length();
  int len = str.length();
  if(key_length < len){
    for(int i = 0; i < len - key_length + 1; i++){
      if(str.substr(i, key_length)==text){
        indices.push_back(i);
      }
    }
  }
  else if(key_length == len && len != 0){
    (str == text) ? indices.push_back(0):indices.push_back(-1);
  }
  else{
    indices.push_back(-1);
  }
  return indices;
}

//tworzymy tablice przesuniec, ktora pomoze nam w ustawianiu wzorca wzgledem tekstu
void initShifts(std::string const &text, int kmpShifts[], int s)
{
    int i, j;

    i = 0;
    j = kmpShifts[0] = -1;
    while(i < s){
        while(j > -1 && text[i] != text[j]){
            j = kmpShifts[j];
        }
        i++;
        j++;

        if(text[i] == text[j])
            kmpShifts[i] = kmpShifts[j];
        else
            kmpShifts[i] = j;
    }
}

Index findKMP(std::string &str, std::string &text)
{
    Index results;
    int m = str.size();
    int n = text.size();

    if(m == 0 || n == 0){
        std::cout << "Jeden z tekstów jest pusty!" << std::endl;
        results.push_back(-1);
        return results;
    } else if(m == n){
        (str == text) ? results.push_back(0) : results.push_back(-1);
        return results;
    } else if(m > n){
        std::cout << "Wzorzec dluzszy od tekstu!" << std::endl;
        results.push_back(-1);
        return results;
    }

    int i, j, kmpShifts[m];
    initShifts(str, kmpShifts, m);

    i = j = 0;
    while(j < n){
        while(i > -1 && str[i] != text[j])
            i = kmpShifts[i];
        i++;
        j++;

        if(i >= m){
            results.push_back(j - i);
            i = kmpShifts[i];
        }
    }

    if(results.size() == 0){
        std::cout << "Nie znaleziono wzorca." << std::endl;
        results.push_back(-1);
    }

    return results;
}

  

int main(){
  srand(time(0));
  std::string text = randomize(100000);
  std::string str = randomize(7);
  std::cout << "Wzorzec: " << str << std::endl << "Brute: " << std::endl;
  auto t1 = std::chrono::high_resolution_clock::now();
  Index resultsB = BruteFind(str, text);
  auto t2 = std::chrono::high_resolution_clock::now();
  auto dt1 = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);
  t1 = std::chrono::high_resolution_clock::now();
  Index results = findKMP(str, text);
  t2 = std::chrono::high_resolution_clock::now();
  auto dt2 = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);
  for(int result : resultsB){
      std::cout << result << ' ';
  }
  std::cout << std::endl << "KMP: " << std::endl;
  for(int result : results){
      std::cout << result << ' ';
  }
  std::cout << std::endl << "Brute " << dt1.count() << "KMP " << dt2.count() << std::endl;
}