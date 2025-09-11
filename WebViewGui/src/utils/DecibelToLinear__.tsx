export default function DecibelToLinear(db: number) {
  let linear;
  if (db > -144.0) {
    linear = Math.pow(10.0, db / 20.0);
  } else {
    linear = 0.0;
  }

  return linear;
}
