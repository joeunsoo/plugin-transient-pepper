import ToggleButton, { type ToggleButtonProps } from '@mui/material/ToggleButton';

export default function BlurToggleButton(props: ToggleButtonProps) {
  const { onMouseDown, onClick, ...rest } = props;

  const handleMouseDown = (e: React.MouseEvent<HTMLButtonElement>) => {
    onMouseDown?.(e);
    e.preventDefault();
  };

  // eslint-disable-next-line @typescript-eslint/no-explicit-any
  const handleClick = (e: React.MouseEvent<HTMLElement, MouseEvent>, value: any) => {
    (e.currentTarget as HTMLElement).blur(); // 클릭 후 포커스 제거
    if (onClick) onClick(e, value);
  };

  return <ToggleButton
    {...rest}
    onMouseDown={handleMouseDown}
    onClick={handleClick}
  />;
}
