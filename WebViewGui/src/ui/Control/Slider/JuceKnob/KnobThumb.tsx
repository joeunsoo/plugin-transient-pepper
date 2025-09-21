export interface KnobProps {
  value: number
}

export default function Component({
  value
}: KnobProps) {
  return (
    <g
      transform={`
        translate(100 100)
        rotate(${(value * 270) + 45})
      `}
    >
      <line
        x1={0}
        y1={15}
        x2={0}
        y2={45}
        strokeWidth="8"
        strokeLinecap="round"
        stroke="var(--mantine-color-white)"
      />
    </g>
  );
}
