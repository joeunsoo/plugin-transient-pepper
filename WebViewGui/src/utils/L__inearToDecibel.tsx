export default function LinearToDecibel(linear: number) {
  let db;
  if (linear > 0.0) {
    db = 20.0 * Math.log10(linear);
  } else {
    db = -144.0; // 사실상 마이너스 무한대 처리
  }

  return db;
}
