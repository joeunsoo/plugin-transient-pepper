export interface KnobProps {
  value: number
}

export default function Component({
  value
}: KnobProps) {
  const distance = 80;

  const angle0 = (1 * 270) - 180;
  const isAngle = ((1-value) * 270) - 180;
  const radian0 = angle0 * Math.PI / 180;
  const x0 = distance * Math.cos(radian0);
  const y0 = distance * Math.sin(radian0);

  const angle1 = (value * 270) - 180;
  const radian1 = angle1 * Math.PI / 180;
  const x1 = distance * Math.cos(radian1);
  const y1 = distance * Math.sin(radian1);

  return (
    <g
      transform="
        translate(100 100)
        rotate(-45)
      "
    >
      <path
        d={`
          M ${x1} ${y1}
          A ${distance} ${distance} 0 ${isAngle < 0 ? 0 : 1} 1 ${x0} ${y0}
        `}
        fill="none"
        stroke="var(--mui-palette-primary-lighter)"
        strokeWidth="10"
        style={{}}
      />
      <path
        d={`
          M ${-distance} 0
          A ${distance} ${distance} 0 ${angle1 < 0 ? 0 : 1} 1 ${x1} ${y1}
        `}
        fill="none"
        stroke="var(--mui-palette-primary-dark)"
        strokeWidth="10"
        style={{}}
      />
    </g>
  );
}
