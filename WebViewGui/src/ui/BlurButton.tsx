import Button, { type ButtonProps } from '@mui/material/Button';

export default function BlurButton(props: ButtonProps) {
  const { onMouseDown, onClick, ...rest } = props;

  const handleMouseDown = (e: React.MouseEvent<HTMLButtonElement>) => {
    onMouseDown?.(e);
    e.preventDefault();
  };

  const handleClick = (e: React.MouseEvent<HTMLButtonElement>) => {
    (e.currentTarget as HTMLElement).blur(); // 클릭 후 포커스 제거
    if (onClick) onClick(e);
  };

  return <Button {...rest} onMouseDown={handleMouseDown} onClick={handleClick} />;
}
