// 1. PRODUCT: The complex object to construct
class HolidayPackage {
    private String flight;
    private String hotel;
    private String activity;

    public void setFlight(String flight) { this.flight = flight; }
    public void setHotel(String hotel) { this.hotel = hotel; }
    public void setActivity(String activity) { this.activity = activity; }

    public void showPackageDetails() {
        System.out.println("--- Holiday Package ---");
        System.out.println("Flight:   " + flight);
        System.out.println("Hotel:    " + hotel);
        System.out.println("Activity: " + activity);
        System.out.println();
    }
}

// 2. ABSTRACT BUILDER: Defines the steps
interface HolidayPackageBuilder {
    void buildFlight();
    void buildHotel();
    void buildActivity();
    HolidayPackage getPackage();
}

// 3. CONCRETE BUILDER 1: Adventure Package
class AdventurePackageBuilder implements HolidayPackageBuilder {
    private HolidayPackage pkg = new HolidayPackage();

    public void buildFlight() { pkg.setFlight("Economy Flight"); }
    public void buildHotel() { pkg.setHotel("Mountain Cabin"); }
    public void buildActivity() { pkg.setActivity("Hiking Tour"); }

    public HolidayPackage getPackage() { return this.pkg; }
}

// 4. CONCRETE BUILDER 2: Relaxation Package
class RelaxationPackageBuilder implements HolidayPackageBuilder {
    private HolidayPackage pkg = new HolidayPackage();

    public void buildFlight() { pkg.setFlight("Business Class Flight"); }
    public void buildHotel() { pkg.setHotel("5-Star Resort"); }
    public void buildActivity() { pkg.setActivity("Spa Treatment"); }

    public HolidayPackage getPackage() { return this.pkg; }
}

// 5. DIRECTOR: Controls the construction sequence
class PackagePlanner {
    public void constructPackage(HolidayPackageBuilder builder) {
        builder.buildFlight();
        builder.buildHotel();
        builder.buildActivity();
    }
}

// 6. MAIN / DEMO
public class Main {
    public static void main(String[] args) {
        PackagePlanner planner = new PackagePlanner();

        // Build Adventure Package
        HolidayPackageBuilder adventureBuilder = new AdventurePackageBuilder();
        planner.constructPackage(adventureBuilder);
        HolidayPackage adventurePackage = adventureBuilder.getPackage();
        adventurePackage.showPackageDetails();

        // Build Relaxation Package using the SAME construction process
        HolidayPackageBuilder relaxationBuilder = new RelaxationPackageBuilder();
        planner.constructPackage(relaxationBuilder);
        HolidayPackage relaxationPackage = relaxationBuilder.getPackage();
        relaxationPackage.showPackageDetails();
    }
}