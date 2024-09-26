import java.beans.BeanInfo;
import java.beans.Introspector;

public class hello {
    public static void main(String[] args) throws Exception {
        BeanInfo beanInfo = Introspector.getBeanInfo(Person.class);
        for(var info : beanInfo.getPropertyDescriptors()) {
            System.out.println(info.getName());
            System.out.println(info.getReadMethod());
            System.out.println(info.getWriteMethod());
        }
    }
}

class Person {
    private String name;
    private int age;

    public int getAge() {
        return age;
    }

    public void setAge(int age) {
        this.age = age;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }
}

