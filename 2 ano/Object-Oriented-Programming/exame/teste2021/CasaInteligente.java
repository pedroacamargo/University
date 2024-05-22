import java.util.Collection;
import java.util.Map;
import java.util.stream.Collectors;

public class CasaInteligente {
    Collection<SmartDevice> devices;
    Map<String, Collection<SmartDevice>> devicesMap;

    public CasaInteligente(Collection<SmartDevice> devices) {
        this.devices = devices.stream().map(SmartDevice::clone).collect(Collectors.toList());
    }

}
