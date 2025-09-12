export default function generatePathData(
  values: number[],      // 기존 값 배열
  newValue: number,      // 새로 들어온 값
  maxPoints: number,     // 최대 포인트 수
  width: number,         // SVG width
  height: number         // SVG height
): { newValues: number[], pathData: string } {

  // 1. 배열 업데이트 (고정 길이)
  const updatedValues = [...values, newValue];
  if (updatedValues.length > maxPoints) {
    updatedValues.shift(); // 오래된 값 제거
  }

  // 2. pathData 생성
  const stepX = width / (maxPoints - 1); // x 간격
  const pathDataLine = updatedValues
    .map((v, i) => {
      const x = i * stepX;
      const y = height - v * height; // v는 0~1로 정규화된 값

      return `${i === 0 ? 'L' : 'L'}${x},${y}`;
    })
    .join(' ');
  const pathData = `M -10,${height} ${pathDataLine} L ${width + 10},${height}`;

  return { newValues: updatedValues, pathData };
}
