package expression;

public class Or extends AbstractBinaryOperator {
    public Or(final TripleExpression first, final TripleExpression second) {
        super(first, second);
    }

    protected int calculate(final int first, final int second) {
        return first | second;
    }
}
