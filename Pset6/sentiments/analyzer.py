import nltk

class Analyzer():
    """Implements sentiment analysis."""

    def __init__(self, positives="positive-words.txt", negatives="negative-words.txt"):
        """Initialize Analyzer."""
        
        self.posWord = set()
        self.negWord = set()
        
        file = open(positives, "r")
        for line in file:
            if line.find(';'):
                self.posWord.add(line.rstrip("\n"))
        file.close()
        
        file = open(negatives, "r")
        for line in file:
            if line.find(';'):
                self.negWord.add(line.rstrip("\n"))
        file.close()


    def analyze(self, text):
        """Analyze text for sentiment, returning its score."""
        
        # TODO
        tokenizer = nltk.tokenize.TweetTokenizer()
        tokens = tokenizer.tokenize(text.lower())
        count = 0
        for i in self.posWord:
            for j in tokens:
                if j == i:
                    count += 1
        for i in self.negWord:
            for j in tokens:
                if j == i:
                    count -= 1
        return count