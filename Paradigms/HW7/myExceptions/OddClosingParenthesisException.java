package myExceptions;

public class OddClosingParenthesisException extends ParsingException {
    public OddClosingParenthesisException(final String s, int ind) {
        super("Odd closing parenthesis at position: " + ind + "\n" + s + "\n" + getPlace(ind, 1));
    }
}
