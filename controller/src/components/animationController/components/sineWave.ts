export default class {
  private pos: number;

  constructor() {
    this.pos = 0;
  }

  public getValues(log: boolean) {
    if (this.pos == 360) this.pos = 0;

    const largeAngleRad = this.pos * (Math.PI / 180); // convert to radians
    const largeValue = Math.sin(largeAngleRad); // grab the sine of the angle, -1 to +1
    const largeDistance = ((largeValue + 1) / 2) * 100; // convert to percentage with 0 being at the 50% mark

    const smallAngleRad = (180 + this.pos) * (Math.PI / 180); // convert to radians
    const smallValue = Math.sin(smallAngleRad); // -1 to +1
    const smallDistance = ((smallValue + 1) / 2) * 100; // 0 to 1
    const message = `${largeDistance.toFixed(0).toString().padStart(2, "0")},${smallDistance.toFixed(0).toString().padStart(2, "0")}`;
    if (log) console.log("Sine Wave: ", message);

    this.pos += 1;

    return message;
  }
}
