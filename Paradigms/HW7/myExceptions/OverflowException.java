package myExceptions;

public class OverflowException extends EvaluatingException {
    public OverflowException() {
        super("overflow");
    }
}
