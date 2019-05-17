package expression;

public class Divide extends AbstractBinaryOperator {
    public Divide(final TripleExpression first, final TripleExpression second) {
        super(first, second);
    }

    protected int calculate(final int first, final int second) {
        return first / second;
    }
}
