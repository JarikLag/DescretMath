package myExceptions;

public class OddOpeningParenthesisException extends ParsingException {
    public OddOpeningParenthesisException(final String s, final int ind) {
        super("Odd opening parenthesis at position: " + ind + "\n" + s + "\n" + getPlace(ind, 1));
    }
}
