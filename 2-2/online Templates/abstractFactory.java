interface iEnemy{
    public void spawn();
}
interface iWeapon{
    public void attack();
}

interface WorldThemeFactory{
    public iEnemy createEnemy();
    public iWeapon createWeapons();
}

class Cyborg implements iEnemy{
    public void spawn(){
        System.out.println("Spawns a cybernetically enhanced assassin");
    }
}
class Orc implements iEnemy{
    public void spawn(){
        System.out.println("Spawns an armored Orc warrior");
    }
}
class plasmaRiffle implements iWeapon{
    public void attack(){
   System.out.println("Attacks a plasma Riffle");
    }
}
class MagicStaff implements iWeapon{
    public void attack(){
        System.out.println("Attacks a magic Staff");
    }
}

class Cyberpunk implements WorldThemeFactory{
   public iWeapon createWeapons(){
       return new plasmaRiffle();
   }
   public iEnemy createEnemy(){
       return new Cyborg();
   }
}
class HighFantasy implements WorldThemeFactory{
    @Override
    public iEnemy createEnemy(){
        return new Orc();
    }

    @Override
    public iWeapon createWeapons() {
        return new MagicStaff();
    }
}

class CombatEncounter{
   WorldThemeFactory worldThemeFactory;
   private iEnemy enemy;
   private iWeapon weapon;
   CombatEncounter(WorldThemeFactory worldThemeFactory){
       this.worldThemeFactory = worldThemeFactory;
       enemy= worldThemeFactory.createEnemy();
       weapon= worldThemeFactory.createWeapons();
   }
   public void play(){
       enemy.spawn();
       weapon.attack();
   }
}
public class Main {
    public static void main(String[] args) {
        WorldThemeFactory hf=new HighFantasy();
        CombatEncounter game=new CombatEncounter(hf);
        game.play();
    }
}
