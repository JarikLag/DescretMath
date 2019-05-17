package expression;

public class Subtract extends AbstractBinaryOperator {
    public Subtract(final TripleExpression first, final TripleExpression second) {
        super(first, second);
    }

    protected int calculate(final int first, final int second) {
        return first - second;
    }
}
