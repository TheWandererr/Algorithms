import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.PrintStream;
import java.util.List;
import java.util.*;

public class Main {

    public static class Translator {

        private String inFile;
        private String phoneNumber;
        private String count;
        private List<String> wordsToUse;
        private Alphabet alphabet;
        private Map<String, String> wordsToNumbers;
        private List<String> answer;

        public Translator() {
            inFile = "in.txt";
            phoneNumber = "";
            alphabet = new Alphabet();
            wordsToNumbers = new HashMap<>();
            answer = new LinkedList<>();
            wordsToUse = new ArrayList<>();
        }

        public void readFile() throws Exception {
            File file = new File(inFile);
            if (file.length() != 0) {
                String tmp;
                try (Scanner sc = new Scanner(file)) {
                    if (sc.hasNextLine()) {
                        phoneNumber = sc.nextLine().trim();
                    }
                    if (sc.hasNextLine()) {
                        count = sc.nextLine();
                    }
                    while (sc.hasNextLine()) {
                        tmp = sc.nextLine().trim();
                        if (tmp.length() <= phoneNumber.length())
                            wordsToUse.add(tmp);
                    }
                }
            }
        }

        private String translate(char[] arr) {
            StringBuilder out = new StringBuilder();
            Map<Character, Integer> alpha = alphabet.getAlphabet();
            for (char symbol : arr) {
                if (symbol >= 'A' && symbol <= 'Z') {
                    out.append(alpha.get(symbol));
                } else {
                    out.append(symbol);
                }
            }
            return out.toString();
        }

        public void refactor() {
            char[] arr;
            String translated;
            for (String word : wordsToUse) {
                arr = word.toCharArray();
                translated = translate(arr);
                wordsToNumbers.put(translated, word);
            }
        }

        private void checkAnswer() {
            int len = 0;
            for (String item : answer) {
                len += item.length();
            }
            if (len != phoneNumber.length()) {
                answer.clear();
            }
        }

        public void writeAnswer() throws Exception {
            findSolution();
            checkAnswer();
            try (PrintStream ps = new PrintStream("out.txt")) {
                if (answer.size() == 0) {
                    ps.println("No solution");
                } else {
                    ps.println(answer.size());
                    StringBuilder sb = new StringBuilder();
                    for (String item : answer) {
                        sb.append(item);
                        sb.append(" ");
                    }
                    ps.println(sb.toString().trim());
                }
            }
        }

        private void findSolution() {
            ArrayList<LinkedList<String>> subTask = new ArrayList<>();
            char[] symbols = this.phoneNumber.toCharArray();
            StringBuilder subNumber = new StringBuilder();
            int index = symbols.length;
            String currentSubstringOfNumber;
            LinkedList<String> currentSolution = new LinkedList<>();
            StringBuilder tmp = new StringBuilder();
            List<LinkedList<String>> tmpSolution = new ArrayList<>();
            for (int i = index - 1; i >= 0; --i) {
                subNumber.insert(0, symbols[i]);
                currentSubstringOfNumber = subNumber.toString();
                if (wordsToNumbers.containsKey(currentSubstringOfNumber)) {
                    currentSolution.add(0, wordsToNumbers.get(currentSubstringOfNumber));
                    subTask.add(0, new LinkedList<>(currentSolution));
                    currentSolution.clear();
                } else {
                    if (i != index - 1) {
                        int j = 0;
                        int k = i;
                        tmp.setLength(0);
                        for (; k < phoneNumber.length() - 1; k++) {
                            tmp.append(symbols[k]);
                            if (wordsToNumbers.containsKey(tmp.toString())) {
                                currentSolution = new LinkedList<>(subTask.get(j));
                                currentSolution.add(0, wordsToNumbers.get(tmp.toString()));
                                tmpSolution.add(new LinkedList<>(currentSolution));
                                currentSolution.clear();
                            }
                            j++;
                        }
                        if (tmpSolution.size() != 0) {
                            int min = tmpSolution.get(0).size();
                            int indexOfMin = 0;
                            int tmpIndexOfMin = 0;
                            for (List<String> item : tmpSolution) {
                                if (item.size() < min && !item.contains("-()-")) {
                                    indexOfMin = tmpIndexOfMin;
                                }
                                tmpIndexOfMin++;
                            }
                            subTask.add(0, tmpSolution.get(indexOfMin));
                            currentSolution.clear();
                            tmpSolution.clear();
                        } else {
                            LinkedList<String> lst = new LinkedList<>(subTask.get(0));
                            lst.addFirst("-()-");
                            subTask.add(0, new LinkedList<>(lst));
                            lst.clear();
                        }
                    } else {
                        subTask.add(0, new LinkedList<>());
                    }
                }
            }
            answer = new LinkedList<>(subTask.get(0));
        }
    }

    public static class Alphabet {
        private Map<Character, Integer> dict;

        public Alphabet() {
            dict = new HashMap<>();
            dict.put('A', 2);
            dict.put('B', 2);
            dict.put('C', 2);
            dict.put('D', 3);
            dict.put('E', 3);
            dict.put('F', 3);
            dict.put('G', 4);
            dict.put('H', 4);
            dict.put('I', 1);
            dict.put('J', 1);
            dict.put('K', 5);
            dict.put('L', 5);
            dict.put('M', 6);
            dict.put('N', 6);
            dict.put('O', 0);
            dict.put('P', 7);
            dict.put('Q', 0);
            dict.put('R', 7);
            dict.put('S', 7);
            dict.put('T', 8);
            dict.put('U', 8);
            dict.put('V', 8);
            dict.put('W', 9);
            dict.put('X', 9);
            dict.put('Y', 9);
            dict.put('Z', 0);
        }

        public Map getAlphabet() {
            return dict;
        }
    }

    public static void main(String[] args){
        try {
            Translator tl = new Translator();
            tl.readFile();
            tl.refactor();
            tl.writeAnswer();
        }
        catch (Exception e){
            try(PrintStream ps = new PrintStream(new File("out.txt"))){
                ps.println("No solution");
            }
            catch (Exception exc){

            }
        }
    }
}



