[@react.component]
let make = (~additionalInfo="") => {
  <div>
    {ReasonReact.string(
       additionalInfo
       ++ " There was an error, please contact be at aaronalexander.inc@gmail.com",
     )}
  </div>;
};
