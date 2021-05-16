[@react.component]
let make = () => {
  let url = ReasonReact.Router.useUrl();

  switch (url.path) {
  | [] => <RecentConfessionsPage />
  | ["submit"] => <SubmitConfessionPage />
  | ["comments", id] => <ConfessionPage id />
  | _ => <NotFoundPage />
  };
};
