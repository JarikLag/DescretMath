package expression;


public class Variable implements TripleExpression {
    private final char name;

    public Variable(final char name) {
        this.name = name;
    }

    public Variable(final String name) {
        this.name = name.charAt(0);
    }

    public int evaluate(final int x, final int y, final int z) {
        switch (name) {
            case 'x':
                return x;
            case 'y':
                return y;
            case 'z':
                return z;
            default:
                return 0;
        }
    }

}
