
[@react.component]
let make = () => {
  let url = ReasonReact.Router.useUrl();

  switch (url.path) {
   //| [] => <TopStoriesPage />
  | [] => <RecentConfessionsPage />
  | ["submit"] => <SubmitPage  />
  | ["comments", id] => <CommentsPage id=int_of_string(id) />
  | _ => <NotFound />
  };
};
