import { MqttClient } from "mqtt/*";
import PerlinNoise from "./components/perlinNoise";
import SineWave from "./components/sineWave";

export default class {
  perlinNoise: PerlinNoise;
  sineWave: SineWave;
  client: MqttClient;
  state: string;

  constructor(client: MqttClient) {
    this.state = "idle";

    this.perlinNoise = new PerlinNoise();
    this.sineWave = new SineWave();
    this.client = client;
  }

  tick() {
    switch (this.state) {
      case "perlin":
        const sin = this.perlinNoise.getNoiseValues();
        this.client.publish("Diamonds Control", sin);
        break;

      case "sine":
        const sine = this.sineWave.getValues();
        this.client.publish("Diamonds Control", sine);
        break;

      case "idle":
        break;

      default:
        break;
    }
  }

  public perlin() {
    this.state = "perlin";
  }

  public sine() {
    this.state = "sine";
  }

  public idle() {
    this.state = "idle";
  }
}
