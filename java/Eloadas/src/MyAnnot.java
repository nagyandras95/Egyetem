import static java.lang.annotation.ElementType.FIELD;
import static java.lang.annotation.ElementType.METHOD;
import static java.lang.annotation.ElementType.TYPE;
import static java.lang.annotation.RetentionPolicy.RUNTIME;

import java.lang.annotation.Retention;
import java.lang.annotation.Target;

//@Target(ElementType.METHOD)
@Target({METHOD, TYPE, FIELD})
@Retention(RUNTIME)
public @interface MyAnnot {
	String value() default "";
	int year() default 2017;
}
